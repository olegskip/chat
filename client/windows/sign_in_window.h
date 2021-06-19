#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QLabel>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QShortcut>
#include <QMessageBox>

#include "server/server.h"
#include <windows/account_recovery_window.h>


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
	QMessageBox messageBox;

	QScopedPointer<QShortcut> sigInShortcut;
	void enterPressed();
	QScopedPointer<QShortcut> backShortcut;
	void escapePressed();

	Server &server = Server::getInstance();

	void recoverAccount();
	QScopedPointer<AccountRecoveryWindow> accountRecoveryWindow;
};

#endif // SIGNINWINDOW_H
