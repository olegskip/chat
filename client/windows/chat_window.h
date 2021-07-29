#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>

class ChatWindow: public QWidget
{
public:
	explicit ChatWindow(QWidget *parent = nullptr) noexcept;
};

#endif // CHATWINDOW_H
