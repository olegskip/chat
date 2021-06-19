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
		std::istream is(&buffer);
		is >> dataString;
		packetsManager.splitPackets(dataString);
		readData();
	});
}

void Session::processPacket(std::shared_ptr<Packet> packet)
{
}
