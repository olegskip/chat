#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>

#include "widgets/messages_box.h"
#include "server_connection/server_connection.h"


class ChatWindow: public QWidget
{
public:
	explicit ChatWindow(QString &&username_) noexcept;

private:
	QVBoxLayout mainLayout;
	MessagesBox messagesBox;

	QPlainTextEdit messageInput;
	QPushButton sendMessageButton;
	QHBoxLayout newMessageLayout;

	void sendNewMessage() noexcept;
	void processNewMessages(MessagesPtrQueue messages) noexcept; // when somebody sends a message this function is to be executed
	void processOldMessages(MessagesPtrQueue messages) noexcept; // when a user scrolls up and wants to laod more messages this function is to be executed

	void messagesScrolled(int value) noexcept;

	const QString username;

	ServerConnection &serverConnection = ServerConnection::getInstance();
};

#endif // CHATWINDOW_H
