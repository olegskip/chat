#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QTimer>

#include "sign_up_window.h"
#include "log_in_window.h"


class StartWindow : public QWidget
{
	Q_OBJECT

public:
	explicit StartWindow(QWidget *parent = nullptr) noexcept;
	~StartWindow() noexcept;

private:
	QHBoxLayout buttonsLayout;
	QPushButton signUpButton;
	QPushButton logInButton;

	QScopedPointer<SignUpWindow> signUpWindow;
	QScopedPointer<LogInWindow> logInWindow;

	void showSignUpWindow() noexcept;
	void showLogInWindow() noexcept;
};
#endif // STARTWINDOW_H
