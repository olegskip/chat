#include "chat_window.h"

ChatWindow::ChatWindow() noexcept
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

	connect(&serverConnection, &ServerConnection::gotNewMessagesSignal, this, &ChatWindow::processNewMessages);
	serverConnection.startProcessingMessages();
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
		messagesBox.appendNewMessage(messages.back());
		messages.pop();
	}
}

