#include "server.h"

Server::Server(): tcpAcceptor(tcp::acceptor(io_context, tcp::endpoint(boost::asio::ip::tcp::v4(), 6789)))
{
	acceptConnections();
	io_context.run();
}

void Server::acceptConnections()
{
	tcpAcceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket)
	{
		sessions.push_back(std::make_shared<Session>(std::move(socket)));
		acceptConnections();
	});
}