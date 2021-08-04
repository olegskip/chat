#include "session.h"

Session::Session(tcp::socket socket) noexcept
	:sessionSocket(std::move(socket))
{
	std::cout << "New session!" << std::endl;
	readData();
}

void Session::postNewMessages(MessagesPtrQueue &&messages)
{
	if(username.empty() || messages.empty()) {
		std::cout << "return" << std::endl;
		return;
	}

	nlohmann::json jsonResponse;
	jsonResponse["type"] = static_cast<int>(RequestsTypes::NEW_MESSAGES);

	nlohmann::json messagesJson = nlohmann::json::array();
	while(!messages.empty()) {
		nlohmann::json message;
		message["sender"] = messages.back()->senderUsername;
		message["text"] = messages.back()->messageText;
		messagesJson.push_back(message);
		messages.pop();
	}
	jsonResponse["messages"] = messagesJson;
	const std::string responseText = jsonResponse.dump();
	std::cout << "response = " << responseText << std::endl;

	sessionSocket.async_send(boost::asio::buffer(responseText), [this](boost::system::error_code ec, size_t length)
	{
		if(ec)
			std::cerr << "Can't send to" << sessionSocket.remote_endpoint().address() << " Error = " << ec.message() << std::endl;
	});
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
			else
				responseCode = static_cast<int>(ResponsesCodes::INCORRECT_PASSWORD_CANNOT_LOG_IN);
		}
		else {
			responseCode = static_cast<int>(ResponsesCodes::NO_SUCH_USERNAME_CANNOT_LOG_IN);
		}
	}

	nlohmann::json jsonResponse;
	jsonResponse["type"] = static_cast<int>(RequestsTypes::LOG_IN);
	jsonResponse["code"] = responseCode;
	const std::string responseText = jsonResponse.dump();
	std::cout << "response = " << responseText << std::endl;

	sessionSocket.async_send(boost::asio::buffer(responseText), [this](boost::system::error_code ec, size_t length)
	{
		if(ec)
			std::cerr << "Can't send to" << sessionSocket.remote_endpoint().address() << " Error = " << ec.message() << std::endl;
	});
}

void Session::processSignUpRequest(const std::string &username, const std::string &password) noexcept
{
	int responseCode = -1;
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
	const std::string responseText = jsonResponse.dump();
	std::cout << "response = " << responseText << std::endl;

	sessionSocket.async_send(boost::asio::buffer(responseText), [this](boost::system::error_code ec, size_t length)
	{
		if(ec)
			std::cerr << "Can't send to" << sessionSocket.remote_endpoint().address() << " Error = " << ec.message() << std::endl;
	});
}

void Session::processPostMessageRequest(const std::string &messageText)
{
	if(username.empty() || messageText.empty())
		return;
	newMessagesSignal(MessagesPtrQueue({std::make_unique<Message>(username, messageText)}));
	databaseManager.addMessage(Message(username, messageText));
}
