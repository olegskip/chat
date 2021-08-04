#include "sign_up_window.h"

SignUpWindow::SignUpWindow(QWidget *parent) noexcept
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
	mainLayout.addWidget(&passwordInput, 30);

	passwordConfirmationInput.setParent(this);
	passwordConfirmationInput.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	passwordConfirmationInput.setPlaceholderText("confirm your password");
	mainLayout.addWidget(&passwordConfirmationInput, 30);

	mainLayout.addLayout(&buttonsLayout);

	goBackButton.setParent(this);
	goBackButton.setText("← Back");
	goBackButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&goBackButton, &QPushButton::clicked, this, &SignUpWindow::goBackSignal);
	buttonsLayout.addWidget(&goBackButton);

	signUpButton.setParent(this);
	signUpButton.setText("Sign up →");
	signUpButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&signUpButton, &QPushButton::clicked, this, &SignUpWindow::askToSendSignUpRequest);
	buttonsLayout.addWidget(&signUpButton);

	enterShortcut.reset(new QShortcut(QKeySequence("Return"), this));
	connect(enterShortcut.get(), &QShortcut::activated, this, &SignUpWindow::enterPressed);

	escapeShortcut.reset(new QShortcut(QKeySequence("Escape"), this));
	connect(escapeShortcut.get(), &QShortcut::activated, this, &SignUpWindow::escapePressed);
}

void SignUpWindow::askToSendSignUpRequest() noexcept
{
	setDisabled(true);
	const QString username = usernameInput.text();
	const QString password = passwordInput.text();
	const QString passwordConfirmation = passwordConfirmationInput.text();

	if(username.isEmpty()) {
		showInformativeDialog("Error", "Invalid username", geometry());
	}
	else if(password.isEmpty()) {
		showInformativeDialog("Error", "Invalid password", geometry());
	}
	else if(password != passwordConfirmation) {
		showInformativeDialog("Error", "Invalid confirmation password", geometry());
	}
	else {
		connect(&serverConnection, &ServerConnection::gotSignUpResponseSignal, this, &SignUpWindow::processSignUpResponse);
		serverConnection.sendSignUpRequest(username, password);
	}
}

void SignUpWindow::processSignUpResponse(int responseCode) noexcept
{
	setDisabled(false);
	if(responseCode == static_cast<int>(ResponsesCodes::SUCCESSFULLY_SIGNED_UP)) {
		showInformativeDialog("Information", "The account was successfully created", geometry());
		emit goBackSignal();
	}
	else if(responseCode == static_cast<int>(ResponsesCodes::USERNAME_IS_TAKEN_CANNOT_SIGN_UP))
		showInformativeDialog("Error", "The username is already taken", geometry());
	else if(responseCode == static_cast<int>(ResponsesCodes::INVALID_USERNAME_OR_PASSWORD_TO_SIGN_UP))
		showInformativeDialog("Error", "The server and the client have a conflict. Try to change your login/password or update the client", geometry());
	else
		showInformativeDialog("Error", "There is an unexpected error", geometry());
	disconnect(&serverConnection, &ServerConnection::gotSignUpResponseSignal, this, &SignUpWindow::processSignUpResponse);
}

void SignUpWindow::enterPressed() noexcept
{
	if(usernameInput.hasFocus())
		passwordInput.setFocus();
	else if(passwordInput.hasFocus())
		passwordConfirmationInput.setFocus();
	else if(passwordConfirmationInput.hasFocus())
		askToSendSignUpRequest();
}

void SignUpWindow::escapePressed() noexcept
{
	if(usernameInput.hasFocus())
		usernameInput.clearFocus();
	else if(passwordInput.hasFocus())
		passwordInput.clearFocus();
	else if(passwordConfirmationInput.hasFocus())
		passwordConfirmationInput.clearFocus();
	else
		emit goBackSignal();
}
