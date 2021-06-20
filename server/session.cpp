#include "session.h"

Session::Session(tcp::socket socket): sessionSocket(std::move(socket))
{
	std::cout << "New session!" << std::endl;
	readData();
}

void Session::readData()
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
				processPacket(packetJson);
			}
			packetsManager.clearReadyPackets();
		}
		readData();
	});
}

void Session::processPacket(const std::shared_ptr<boost::property_tree::ptree> packetJson)
{
	const std::string packetType = packetJson->get<std::string>("type");
	const std::string packetId = packetJson->get<std::string>("type");
	if(packetType == "sign_in") {
		processSignIn(packetJson->get<std::string>("username"), packetJson->get<std::string>("password"));
	}
}

void Session::processSignIn(std::string username, std::string password)
{
	const bool result = databaseManager.checkSignIn(username, password);
}
