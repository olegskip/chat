#include "sign_in_window.h"

SignInWindow::SignInWindow(QWidget *parent): QWidget(parent)
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

	backButton.setParent(this);
	backButton.setText("← Back");
	backButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&backButton, &QPushButton::clicked, this, &SignInWindow::showStartWindowSignal);
	buttonsLayout.addWidget(&backButton);

	accountRecoveryButton.setParent(this);
	accountRecoveryButton.setText("Account recovery");
	accountRecoveryButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&accountRecoveryButton, &QPushButton::clicked, this, &SignInWindow::recoverAccount);
	buttonsLayout.addWidget(&accountRecoveryButton);

	signInButton.setParent(this);
	signInButton.setText("Sign in →");
	signInButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&signInButton, &QPushButton::clicked, this, &SignInWindow::signIn);
	buttonsLayout.addWidget(&signInButton);

	mainLayout.addLayout(&buttonsLayout, 40);

	sigInShortcut.reset(new QShortcut(QKeySequence("Return"), this));
	connect(sigInShortcut.get(), &QShortcut::activated, this, &SignInWindow::enterPressed);

	backShortcut.reset(new QShortcut(QKeySequence("Escape"), this));
	connect(backShortcut.get(), &QShortcut::activated, this, &SignInWindow::escapePressed);
}

void SignInWindow::signIn()
{
	const QString userName = usernameInput.text();
	const QString password = passwordInput.text();
	if(userName.isEmpty() || password .isEmpty()) {
		MessageBox messageBox("Error", "Invalid username or password", geometry());
	} else {
		setDisabled(true);
		server.signIn(userName, password);
		connect(&server, &Server::signInResponse, this, &SignInWindow::processSignInResponse);
	}
}

void SignInWindow::processSignInResponse(QString username, bool result)
{
	if(usernameInput.text() == username && result) {
		chatWindow.reset(new ChatWindow());
		chatWindow->show();
		hide();
	}
	else {
		MessageBox messageBox("Error", "Invalid username or password", geometry());
		setDisabled(false);
	}
	disconnect(&server, &Server::signInResponse, this, &SignInWindow::processSignInResponse);
}

void SignInWindow::enterPressed()
{
	if(usernameInput.hasFocus())
		passwordInput.setFocus();
	else if(passwordInput.hasFocus())
		signIn();
}

void SignInWindow::escapePressed()
{
	if(usernameInput.hasFocus())
		usernameInput.clearFocus();
	else if(passwordInput.hasFocus())
		passwordInput.clearFocus();
	else
		emit showStartWindowSignal();
}

void SignInWindow::recoverAccount()
{
	accountRecoveryWindow.reset(new AccountRecoveryWindow());
	connect(accountRecoveryWindow.get(), &AccountRecoveryWindow::showSignInWindowSignal, this, &SignInWindow::show);
	accountRecoveryWindow->show();
	hide();
}
