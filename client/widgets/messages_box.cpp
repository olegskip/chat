#include "messages_box.h"

MessagesBox::MessagesBox(QWidget *parent) noexcept:
	QScrollArea(parent)
{
//	setWidget(&mainWidget);
//	mainLayout.setAlignment(Qt::AlignTop);
//	mainWidget.setLayout(&mainLayout);
//	setWidgetResizable(true);
}

void MessagesBox::appendNewMessage(const std::shared_ptr<const Message> &message)
{
//	const bool isNotScrolled = verticalScrollBar()->maximum() == verticalScrollBar()->value();

//	if(!messagesWidgets.isEmpty() && message->senderUsername == messagesWidgets.back()->senderUsername) {
//		messagesWidgets.back()->appendMessage(message->messageText);
//	}
//	else {
//		messagesWidgets.append(QSharedPointer<MessageWidget>(new MessageWidget(this, *message)));
//		mainLayout.addWidget(messagesWidgets.back().get());
//	}
//	if(isNotScrolled)
//		verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}
