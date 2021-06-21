#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class MessageBox
{
public:
	MessageBox(QString title, QString text, QRect parentGeometry);

private:
	QMessageBox messageBox;
};

#endif // MESSAGEBOX_H
