#include "message_widget.h"

MessageWidget::MessageWidget(QWidget *parent, const Message &message) noexcept:
	QWidget(parent), senderUsername(message.senderUsername)
{
	setLayout(&mainLayout);
	mainLayout.setMargin(0);
	mainLayout.setContentsMargins(0, 0, 0, 0);
	mainLayout.setSpacing(0);
	setMinimumWidth(100);

	senderUsernameWidget.setParent(this);
	senderUsernameWidget.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	senderUsernameWidget.setText(message.senderUsername + ":");
	senderUsernameWidget.setReadOnly(true);
	senderUsernameWidget.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	senderUsernameWidget.setStyleSheet("background-color: transparent; border: none;");
	mainLayout.addWidget(&senderUsernameWidget);

	appendMessage(message.messageText);
}

void MessageWidget::appendMessage(const QString text) noexcept
{
	messageTextWidgets.push_back(QSharedPointer<QTextEdit>(new QTextEdit(this)));
	messageTextWidgets.back()->setParent(this);
	messageTextWidgets.back()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	messageTextWidgets.back()->setText(text);
	messageTextWidgets.back()->setReadOnly(true);
	messageTextWidgets.back()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mainLayout.addWidget(messageTextWidgets.back().get());
	updateWidgetsSize();
}

void MessageWidget::updateWidgetsSize() noexcept
{
	senderUsernameWidget.setFixedHeight(senderUsernameWidget.document()->size().toSize().height() + 4);
	for(auto &messageTextWidget: messageTextWidgets)
		messageTextWidget->setFixedHeight(messageTextWidget->document()->size().toSize().height() + 4);

	QTimer::singleShot(1, this, [this](){
		int messageTextWidgetsHeight = 0;
		for(auto &messageTextWidget: messageTextWidgets)
			messageTextWidgetsHeight += messageTextWidget->height();

		setFixedHeight(senderUsernameWidget.height() + messageTextWidgetsHeight);
	});
}

void MessageWidget::resizeEvent(QResizeEvent *event) // override
{
	if(event->type() == QResizeEvent::Resize)
		updateWidgetsSize();
	QWidget::resizeEvent(event);
}
