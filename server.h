#ifndef SERVER_H
#define SERVER_H

#include "session.h"

class Server
{
public:
	Server();
private:
	boost::asio::io_context io_context;
	tcp::acceptor tcpAcceptor;
	void acceptConnections();
	// void errorHandler(const boost::system::error_code& error, std::size_t bytes_transferred);

	std::vector<std::shared_ptr<Session>> sessions;

};

#endif