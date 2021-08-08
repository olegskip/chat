#ifndef MESSAGES_BOX_H
#define MESSAGES_BOX_H

#include <QSharedPointer>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollBar>
#include <QList>

#include "message_widget.h"
#include "message.h"


class MessagesBox: public QScrollArea
{
public:
	explicit MessagesBox(QWidget *parent = nullptr) noexcept;

	void appendNewMessage(const std::shared_ptr<const Message> &message);
	void appendOldMessage(const std::shared_ptr<const Message> &message);

private:
	QWidget mainWidget;
	QVBoxLayout mainLayout;

	QList<QSharedPointer<MessageWidget>> messagesWidgets;
};


#endif // MESSAGE_BOX_H
