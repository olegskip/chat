#ifndef LOG_IN_WINDOW_H
#define LOG_IN_WINDOW_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QKeyEvent>
#include <QEvent>
#include <QShortcut>

#include "windows/chat_window.h"
#include "widgets/informative_dialog.h"


class LogInWindow: public QWidget
{
	Q_OBJECT

public:
	explicit LogInWindow(QWidget *parent = nullptr) noexcept;

signals:
	void goBackSignal();

private:
	QVBoxLayout mainLayout;

	QLabel informativeLabel; // show if the login or the password are invalid

	QLineEdit usernameInput, passwordInput;

	QHBoxLayout buttonsLayout;
	QPushButton goBackButton; // show the previous window(StartWindow)
	QPushButton logInButton; // ask ServerConnection to send to the server a request to log in

	void askToSendLogInRequest() noexcept;
	void processLogInResponse(int responseCode) noexcept;
	QScopedPointer<ChatWindow> chatWindow;

	QScopedPointer<QShortcut> enterShortcut;
	void enterPressed() noexcept;
	QScopedPointer<QShortcut> escapeShortcut;
	void escapePressed() noexcept;

	ServerConnection &serverConnection = ServerConnection::getInstance();
};

#endif // LOG_IN_WINDOW_H
