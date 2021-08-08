#include "messages_box.h"

MessagesBox::MessagesBox(QWidget *parent) noexcept:
	QScrollArea(parent)
{
	setWidget(&mainWidget);
	mainLayout.setAlignment(Qt::AlignTop);
	mainWidget.setLayout(&mainLayout);
	setWidgetResizable(true);
}

void MessagesBox::appendNewMessage(const std::shared_ptr<const Message> &message)
{
	const bool isAutoScroll = verticalScrollBar()->maximum() == verticalScrollBar()->value();
	if(!messagesWidgets.isEmpty() && message->senderUsername == messagesWidgets.back()->senderUsername) {
		messagesWidgets.back()->appendMessage(message->messageText, true);
	}
	else {
		messagesWidgets.append(QSharedPointer<MessageWidget>(new MessageWidget(this, *message)));
		mainLayout.addWidget(messagesWidgets.back().get());
	}

	if(isAutoScroll) {
		QTimer::singleShot(10, this, [this](){ // the program needs some time to update all widgets
			verticalScrollBar()->setValue(verticalScrollBar()->maximum());
		});
	}
}
#include <QDebug>
void MessagesBox::appendOldMessage(const std::shared_ptr<const Message> &message)
{
//	bool isThereMessage = !messagesWidgets.empty();
	QSharedPointer<MessageWidget> firstMessage;
	if(!messagesWidgets.empty())
		firstMessage = messagesWidgets.front();

	qDebug() << "appendOldMessage, text = " << message->messageText;
	if(!messagesWidgets.isEmpty() && message->senderUsername == messagesWidgets.front()->senderUsername) {
		messagesWidgets.front()->appendMessage(message->messageText, false);
	}
	else {
		messagesWidgets.push_front(QSharedPointer<MessageWidget>(new MessageWidget(this, *message)));
		mainLayout.addWidget(messagesWidgets.back().get());
	}

	if(firstMessage)
		ensureWidgetVisible(firstMessage.get());
}
