#include "log_in_window.h"

LogInWindow::LogInWindow(QWidget *parent) noexcept
	:QWidget(parent)
{
	setLayout(&mainLayout);

	usernameInput.setParent(this);
	usernameInput.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	usernameInput.setPlaceholderText("username");
	mainLayout.addWidget(&usernameInput, 30);

	passwordInput.setParent(this);
	passwordInput.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	passwordInput.setPlaceholderText("password");
	passwordInput.setEchoMode(QLineEdit::Password);
	mainLayout.addWidget(&passwordInput, 30);

	goBackButton.setParent(this);
	goBackButton.setText("← Back");
	goBackButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&goBackButton, &QPushButton::clicked, this, &LogInWindow::goBackSignal);
	buttonsLayout.addWidget(&goBackButton);

	logInButton.setParent(this);
	logInButton.setText("Log in →");
	logInButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&logInButton, &QPushButton::clicked, this, &LogInWindow::askToSendLogInRequest);
	buttonsLayout.addWidget(&logInButton);

	mainLayout.addLayout(&buttonsLayout, 40);

	enterShortcut.reset(new QShortcut(QKeySequence("Return"), this));
	connect(enterShortcut.get(), &QShortcut::activated, this, &LogInWindow::enterPressed);

	escapeShortcut.reset(new QShortcut(QKeySequence("Escape"), this));
	connect(escapeShortcut.get(), &QShortcut::activated, this, &LogInWindow::escapePressed);
}

void LogInWindow::askToSendLogInRequest() noexcept
{
	const QString username = usernameInput.text();
	const QString password = passwordInput.text();
	if(username.isEmpty() || password.isEmpty()) {
		showInformativeDialog("Error", "Invalid username or password", geometry());
		emit goBackSignal();
	} else {
		serverConnection.sendLogInRequest(username, password);
		connect(&serverConnection, &ServerConnection::gotLogInResponseSignal, this, &LogInWindow::processLogInResponse);
	}
	setDisabled(true);
}

void LogInWindow::processLogInResponse(int responseCode) noexcept
{
	if(responseCode == static_cast<int>(ResponsesCodes::SUCCESSFULLY_LOGGED_IN)) {
		chatWindow.reset(new ChatWindow());
		chatWindow->show();
		hide();
	}
	else if(responseCode == static_cast<int>(ResponsesCodes::NO_SUCH_USERNAME_CANNOT_LOG_IN)) {
		showInformativeDialog("Error", "There is no such username", geometry());
	}
	else if(responseCode == static_cast<int>(ResponsesCodes::INCORRECT_PASSWORD_CANNOT_LOG_IN)) {
		showInformativeDialog("Error", "Wrong password", geometry());
	}
	else {
		showInformativeDialog("Error", "There is an unexpected error", geometry());
	}
	setDisabled(false);
	disconnect(&serverConnection, &ServerConnection::gotLogInResponseSignal, this, &LogInWindow::processLogInResponse);
}

void LogInWindow::enterPressed() noexcept
{
	if(usernameInput.hasFocus())
		passwordInput.setFocus();
	else if(passwordInput.hasFocus())
		askToSendLogInRequest();
}

void LogInWindow::escapePressed() noexcept
{
	if(usernameInput.hasFocus())
		usernameInput.clearFocus();
	else if(passwordInput.hasFocus())
		passwordInput.clearFocus();
	else
		emit goBackSignal();
}
