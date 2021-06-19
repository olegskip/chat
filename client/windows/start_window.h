#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "sign_in_window.h"


class StartWindow : public QWidget
{
	Q_OBJECT

public:
	StartWindow(QWidget *parent = nullptr);
	~StartWindow();

private:
	QHBoxLayout buttonsLayout;
	QPushButton createNewAccountButton;
	QPushButton signInButton;

	QScopedPointer<SignInWindow> signInWindow;

private slots:
	void openSignInWindow();
};
#endif // STARTWINDOW_H
