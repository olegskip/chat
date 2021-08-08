#include "chat_window.h"

ChatWindow::ChatWindow(QString &&username_) noexcept:
	username(username_)
{
	setLayout(&mainLayout);
	messagesBox.setParent(this);
	mainLayout.addWidget(&messagesBox);

	messageInput.setParent(this);
	messageInput.setMaximumHeight(100);
	newMessageLayout.addWidget(&messageInput);

	sendMessageButton.setParent(this);
	sendMessageButton.setText("Send");
	connect(&sendMessageButton, &QPushButton::clicked, this, &ChatWindow::sendNewMessage);
	newMessageLayout.addWidget(&sendMessageButton);

	mainLayout.addLayout(&newMessageLayout);

	connect(messagesBox.verticalScrollBar(), &QScrollBar::valueChanged, this, &ChatWindow::messagesScrolled);

	connect(&serverConnection, &ServerConnection::gotNewMessagesSignal, this, &ChatWindow::processNewMessages);
	connect(&serverConnection, &ServerConnection::gotLoadMoreMessagesResponseSignal, this, &ChatWindow::processOldMessages);
	serverConnection.startProcessingMessages();
	serverConnection.sendLoadMoreMessagesRequest();
}

void ChatWindow::sendNewMessage() noexcept
{
	const QString messageText = messageInput.toPlainText();
	if(messageText.isEmpty())
		return;

	messageInput.setPlainText("");
	serverConnection.postNewMessage(messageText);
	messagesBox.appendNewMessage(std::shared_ptr<const Message>(new Message("You", messageText)));
}

void ChatWindow::processNewMessages(MessagesPtrQueue messages) noexcept
{
	while(!messages.empty()) {
		messagesBox.appendNewMessage(messages.front());
		messages.pop();
	}
}

void ChatWindow::processOldMessages(MessagesPtrQueue messages) noexcept
{
	qDebug() << "processOldMessages";
	while(!messages.empty()) {
		messagesBox.appendOldMessage(messages.front());
		messages.pop();
	}
}

void ChatWindow::messagesScrolled(int value) noexcept
{
	if(value == 0) {
		serverConnection.sendLoadMoreMessagesRequest();
	}
}
