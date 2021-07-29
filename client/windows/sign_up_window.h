#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScopedPointer>
#include <QShortcut>

#include "server_connection/server_connection.h"
#include "widgets/message_box.h"


class SignUpWindow: public QWidget
{
	Q_OBJECT

public:
	explicit SignUpWindow(QWidget *parent = nullptr) noexcept;

signals:
	void goBackSignal();

private:
	QVBoxLayout mainLayout;

	QLineEdit emailInput, usernameInput, passwordInput, passwordConfirmationInput;

	QHBoxLayout buttonsLayout;
	QPushButton goBackButton; // show the previous window(StartWindow)
	QPushButton signUpButton; // ask ServerConnection to send to the server a request to sign up the given account

	void askToSendSignUpRequest() noexcept;
	void processSignUpResponse(int responseCode) noexcept;

	QScopedPointer<QShortcut> enterShortcut;
	void enterPressed() noexcept;
	QScopedPointer<QShortcut> escapeShortcut;
	void escapePressed() noexcept;

	ServerConnection &serverConnection = ServerConnection::getInstance();
};

#endif // SIGNUPWINDOW_H
