#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QVBoxLayout>
#include <QString>
#include <QTextDocument>
#include <QTextEdit>
#include <QTimer>
#include <QResizeEvent>

#include "message.h"

class MessageWidget: public QWidget
{
public:
	explicit MessageWidget(QWidget *parent, const Message &message) noexcept;

	const QString senderUsername;
	void appendMessage(const QString text) noexcept;

	~MessageWidget(){}

private:
	QVBoxLayout mainLayout;

//	QTextEdit senderUsernameWidget;
//	QVector<QSharedPointer<QTextEdit>> messageTextWidgets;

	void updateWidgetsSize() noexcept;
	void resizeEvent(QResizeEvent *event) override;
};

#endif // MESSAGE_WIDGET_H
