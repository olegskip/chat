#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>

#include "widgets/messages_box.h"
#include "server_connection/server_connection.h"


class ChatWindow: public QWidget
{
public:
	explicit ChatWindow() noexcept;

private:
	QVBoxLayout mainLayout;
	MessagesBox messagesBox;

	QPlainTextEdit messageInput;
	QPushButton sendMessageButton;
	QHBoxLayout newMessageLayout;

	void sendNewMessage() noexcept;
	void processNewMessages(MessagesPtrQueue messages) noexcept;


	ServerConnection &serverConnection = ServerConnection::getInstance();
};

#endif // CHATWINDOW_H
