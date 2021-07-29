#include "session.h"

Session::Session(tcp::socket socket) noexcept
	:sessionSocket(std::move(socket))
{
	std::cout << "New session!" << std::endl;
	readData();
}

void Session::readData() noexcept
{
	boost::asio::async_read(sessionSocket, buffer, boost::asio::transfer_at_least(1),
		[this](boost::system::error_code ec, size_t length)
	{
		if(!ec) {
			std::istream is(&buffer);
			is >> dataString;
			std::cout << "new data received = " << dataString << std::endl;

			packetsManager.splitPackets(dataString);

			for(auto packetJson: packetsManager.getPacketsJson()) {
				operateRequest(packetJson);
			}
			packetsManager.clearReadyPackets();
		}
		else {
			std::cerr << "Can't read data from" << sessionSocket.remote_endpoint().address() << "\terror = " << ec.message() << std::endl;
		}
		readData();
	});
}

void Session::operateRequest(const std::shared_ptr<boost::property_tree::ptree> &requestJson) noexcept
{
	try {
		const std::string requestType = requestJson->get<std::string>("type");
		if(requestType == convertRequestTypeToString(RequestsTypes::LOG_IN))
			processLogInRequest(requestJson->get<std::string>("username"), requestJson->get<std::string>("password"));
		else if(requestType == convertRequestTypeToString(RequestsTypes::SIGN_UP)) 
			processSignUpRequest(requestJson->get<std::string>("email"), requestJson->get<std::string>("username"), requestJson->get<std::string>("password"));
	}
	catch(const boost::property_tree::ptree_error &e) {
		std::cerr << "Can't parse a request from = " << sessionSocket.remote_endpoint().address() << "\terror = " << e.what()  << std::endl;
	}
}

void Session::processLogInRequest(const std::string &username, const std::string &password) noexcept
{
	int responseCode = -1;
	if(databaseManager.doesUserExist(username)) {
		if(databaseManager.checkLogIn(username, password))
			responseCode = static_cast<int>(ResponsesCodes::SUCCESSFULLY_LOGGED_IN);
		else
			responseCode = static_cast<int>(ResponsesCodes::INCORRECT_PASSWORD_CANNOT_LOG_IN);
	}
	else {
		responseCode = static_cast<int>(ResponsesCodes::NO_SUCH_USERNAME_CANNOT_LOG_IN);
	}

	boost::property_tree::ptree propertyTree;
	propertyTree.put("type", convertRequestTypeToString(RequestsTypes::LOG_IN));
	propertyTree.put("code", responseCode);

	std::stringstream ss;
	boost::property_tree::write_json(ss, propertyTree, false);

	const std::string responseText = boost::trim_right_copy(ss.str());
	std::cout << "response = " << responseText << std::endl;
	sessionSocket.async_send(boost::asio::buffer(responseText), [this](boost::system::error_code ec, size_t length)
	{
		if(ec)
			std::cerr << "Can't send to" << sessionSocket.remote_endpoint().address() << "\terror = " << ec.message() << std::endl;
	});
}

void Session::processSignUpRequest(const std::string &email, const std::string &username, const std::string &password) noexcept
{
	std::cout << "sign up request" << std::endl;
	int responseCode = -1;
	if(databaseManager.doesUserExist(username)) {
		responseCode = static_cast<int>(ResponsesCodes::USERNAME_IS_TAKEN_CANNOT_SIGN_UP);
	}
	else {
		databaseManager.forceToAddUser(email, username, password);
		responseCode = static_cast<int>(ResponsesCodes::SUCCESSFULLY_SIGNED_UP);
	}

	boost::property_tree::ptree propertyTree;
	propertyTree.put("type", convertRequestTypeToString(RequestsTypes::SIGN_UP));
	propertyTree.put("code", responseCode);

	std::stringstream ss;
	boost::property_tree::write_json(ss, propertyTree, false);

	const std::string responseText = boost::trim_right_copy(ss.str());
	std::cout << "response = " << responseText << std::endl;
	sessionSocket.async_send(boost::asio::buffer(responseText), [this](boost::system::error_code ec, size_t length)
	{
		if(ec)
			std::cerr << "Can't send to" << sessionSocket.remote_endpoint().address() << "\terror = " << ec.message() << std::endl;
	});
}
