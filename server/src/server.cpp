#include "server.h"

Server::Server() noexcept
	: tcpAcceptor(tcp::acceptor(io_context, tcp::endpoint(boost::asio::ip::tcp::v4(), 6789)))
{
	acceptConnections();
	io_context.run();
}

void Server::acceptConnections() noexcept
{
	tcpAcceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) noexcept
	{
		sessions.push_back(std::make_shared<Session>(std::move(socket), io_context));
		sessions.back()->newMessagePostedSignal.connect([this, sessionMessageSender = std::weak_ptr<Session>(sessions.back())](std::shared_ptr<const Message> message)
		{
			std::shared_ptr<Session> sessionMessageSenderShared = sessionMessageSender.lock();
			if(sessionMessageSenderShared) {
				if(message->isValid()) {
					for(auto &session: sessions) {
						if(session != sessionMessageSenderShared)
							session->addNewMessageToQueue(message);
					}
				}
			}
		});
		sessions.back()->disconnectSignal.connect([this, disconnectedSession = std::weak_ptr<Session>(sessions.back())]()
		{
			std::shared_ptr<Session> disconnectedSessionShared = disconnectedSession.lock();
			for(auto it = sessions.begin(); it != sessions.end(); ++it) {
				if(*it == disconnectedSessionShared) {
					sessions.erase(it);
					break;
				}
			}
		});

		acceptConnections();
	});
}
