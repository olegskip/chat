#include "session.h"

Session::Session(tcp::socket socket, boost::asio::io_service &ioService) noexcept
	:sessionSocket(std::move(socket)), sendNewMessagesTimer(ioService)
{
	std::cout << "New session!" << std::endl;
	readData();
}

void Session::addNewMessageToQueue(std::shared_ptr<const Message> &message) noexcept
{
	std::lock_guard<std::mutex> lockGuard(sendNewMessagesTimerMutex);
	if(username.empty() || !message->isValid())
		return;
	
	newMessagesToSendQueue.push(message);
	if(!isSendNewMessagesTimerWorking)
		startSendNewMessagesTimer();
}

void Session::readData() noexcept
{
	boost::asio::async_read(sessionSocket, buffer, boost::asio::transfer_at_least(1),
		[this](boost::system::error_code ec, size_t length)
	{
		if(!ec) {
			dataString = std::string(std::istreambuf_iterator<char>(&buffer), {});
			std::cout << "new data received = " << dataString << std::endl;
			packetsManager.splitPackets(dataString);
			for(auto packetJson: packetsManager.getPacketsJson()) {
				operateRequest(packetJson);
			}
			packetsManager.clearReadyPackets();
		}
		else {
			if(ec.value() != boost::asio::error::eof) {
				std::cerr << "Can't read data from" << sessionSocket.remote_endpoint().address() << " But the connection is stil valid. Error = " 
					<< ec.message() << std::endl;
			}
			else {
				std::cerr << "The connection was closed" << std::endl;
				disconnectSignal();
				return;
			}
		}
		readData();
	});
}

void Session::operateRequest(std::shared_ptr<const nlohmann::json> &requestJson) noexcept
{
	try {
		const int requestType = requestJson->at("type");
		if(requestType == static_cast<int>(RequestsTypes::LOG_IN))
			processLogInRequest(requestJson->at("username"), requestJson->at("password"));
		else if(requestType == static_cast<int>(RequestsTypes::SIGN_UP)) 
			processSignUpRequest(requestJson->at("username"), requestJson->at("password"));
		else if(requestType == static_cast<int>(RequestsTypes::NEW_MESSAGES))
			processPostMessageRequest(requestJson->at("message"));
		else if(requestType == static_cast<int>(RequestsTypes::LOAD_MORE_MESSAGES))
			proccessLoadMoreMessagesRequest();
	}
	catch(const nlohmann::json::exception &e) {
		std::cerr << "Can't get a value from = " << sessionSocket.remote_endpoint().address() << " Error = " << e.what()  << std::endl;
	}
}

void Session::processLogInRequest(const std::string &username, const std::string &password) noexcept
{
	int responseCode = -1;
	if(!username.empty() && !password.empty()) {
		if(databaseManager.doesUserExist(username)) {
			if(databaseManager.checkLogIn(username, password)) {
				responseCode = static_cast<int>(ResponsesCodes::SUCCESSFULLY_LOGGED_IN);
				this->username = username;
			}
			else {
				responseCode = static_cast<int>(ResponsesCodes::INCORRECT_PASSWORD_CANNOT_LOG_IN);
			}
		}
		else {
			responseCode = static_cast<int>(ResponsesCodes::NO_SUCH_USERNAME_CANNOT_LOG_IN);
		}
	}

	nlohmann::json jsonResponse;
	jsonResponse["type"] = static_cast<int>(RequestsTypes::LOG_IN);
	jsonResponse["code"] = responseCode;
	jsonResponse["username"] = username;
	sendJson(jsonResponse);
}

void Session::processSignUpRequest(const std::string &username, const std::string &password) noexcept
{
	int responseCode = static_cast<int>(ResponsesCodes::UNEXPECTED_ERROR);
	if(!username.empty() && !password.empty()) {
		if(databaseManager.doesUserExist(username)) {
			responseCode = static_cast<int>(ResponsesCodes::USERNAME_IS_TAKEN_CANNOT_SIGN_UP);
		}
		else {
			databaseManager.forceToAddUser(username, password);
			responseCode = static_cast<int>(ResponsesCodes::SUCCESSFULLY_SIGNED_UP);
		}
	}

	nlohmann::json jsonResponse;
	jsonResponse["type"] = static_cast<int>(RequestsTypes::SIGN_UP);
	jsonResponse["code"] = responseCode;
	sendJson(jsonResponse);
}

void Session::processPostMessageRequest(const std::string &messageText) noexcept
{
	if(username.empty() || messageText.empty())
		return;
	newMessagePostedSignal(std::make_shared<const Message>(username, messageText));
	databaseManager.addMessage(Message(username, messageText));
}

void Session::proccessLoadMoreMessagesRequest() noexcept
{
	if(username.empty())
		return;

	if(oldestMessageVisibleId == -1)
		oldestMessageVisibleId = databaseManager.getMessagesQuantity() + 1;

	MessagesPtrQueue messagesToSend = databaseManager.getOldMessages(oldestMessageVisibleId - 1);
	oldestMessageVisibleId -= messagesToSend.size();

	nlohmann::json jsonResponse;
	jsonResponse["type"] = static_cast<int>(RequestsTypes::LOAD_MORE_MESSAGES);

	int responseCode = static_cast<int>(ResponsesCodes::UNEXPECTED_ERROR);
	if(messagesToSend.empty()) {
		responseCode = static_cast<int>(ResponsesCodes::THERE_ARE_NO_MORE_MESSAGES_CANT_LOAD_MORE);
	}
	else {
		responseCode = static_cast<int>(ResponsesCodes::SUCCESSFULLY_LOADED_MORE_MESSAGES);
		nlohmann::json messagesJson = nlohmann::json::array();
		while(!messagesToSend.empty()) {
			nlohmann::json message;
			message["sender"] = messagesToSend.front()->senderUsername;
			message["text"] = messagesToSend.front()->messageText;
			messagesJson.push_back(message);
			messagesToSend.pop();
		}
		jsonResponse["code"] = responseCode;
		jsonResponse["messages"] = messagesJson;
	}
	sendJson(jsonResponse);
}

void Session::startSendNewMessagesTimer() noexcept
{
	sendNewMessagesTimer.expires_from_now(sendNewMessagesTimerInterval);
	sendNewMessagesTimer.async_wait(std::bind(&Session::sendMessagesFromQueue, this));
	isSendNewMessagesTimerWorking = true;
}

void Session::sendMessagesFromQueue() noexcept
{
	std::lock_guard<std::mutex> lockGuard(sendNewMessagesTimerMutex);
	isSendNewMessagesTimerWorking = false;

	if(username.empty() || newMessagesToSendQueue.empty())
		return;

	nlohmann::json jsonResponse;
	jsonResponse["type"] = static_cast<int>(RequestsTypes::NEW_MESSAGES);

	nlohmann::json messagesJson = nlohmann::json::array();
	while(!newMessagesToSendQueue.empty()) {
		nlohmann::json message;
		message["sender"] = newMessagesToSendQueue.back()->senderUsername;
		message["text"] = newMessagesToSendQueue.back()->messageText;
		messagesJson.push_back(message);
		newMessagesToSendQueue.pop();
	}
	jsonResponse["messages"] = messagesJson;
	sendJson(jsonResponse);
}

void Session::sendJson(const nlohmann::json &json) noexcept
{
	const std::string jsonText = json.dump();
	std::cout << "response = " << jsonText << std::endl;

	sessionSocket.async_send(boost::asio::buffer(jsonText), [this](boost::system::error_code ec, size_t length)
	{
		if(ec)
			std::cerr << "Can't send to" << sessionSocket.remote_endpoint().address() << " Error = " << ec.message() << std::endl;
	});
}

Session::~Session() noexcept
{
	sendNewMessagesTimer.cancel();
}
