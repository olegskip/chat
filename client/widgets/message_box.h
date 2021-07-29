#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>


class MessageBox
{
public:
	// signal are called when the user clicks the ok button
	MessageBox(QString title, QString text, QRect parentGeometry) noexcept;

signals:
	void buttonClicked();

private:
	QMessageBox messageBox;
};

#endif // MESSAGEBOX_H
