#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QLabel>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QKeyEvent>
#include <QEvent>
#include <QShortcut>

#include "server/server.h"
#include "windows/account_recovery_window.h"
#include "windows/chat_window.h"
#include "widgets/message_box.h"


class SignInWindow: public QWidget
{
	Q_OBJECT

public:
	explicit SignInWindow(QWidget *parent = nullptr);

signals:
	void showStartWindowSignal();

private:
	QVBoxLayout mainLayout;

	QLabel informativeLabel;

	QLineEdit usernameInput;
	QLineEdit passwordInput;

	QHBoxLayout buttonsLayout;
	QPushButton backButton;
	QPushButton accountRecoveryButton;
	QPushButton signInButton;

	void signIn();
	void processSignInResponse(QString username, bool result);
	QScopedPointer<ChatWindow> chatWindow;

	QScopedPointer<QShortcut> sigInShortcut;
	void enterPressed();
	QScopedPointer<QShortcut> backShortcut;
	void escapePressed();

	Server &server = Server::getInstance();

	void recoverAccount();
	QScopedPointer<AccountRecoveryWindow> accountRecoveryWindow;
};

#endif // SIGNINWINDOW_H
