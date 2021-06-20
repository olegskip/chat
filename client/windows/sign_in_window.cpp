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
		messageBox.setWindowTitle("Error");
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setText("Invalid username or password");
		messageBox.setIcon(QMessageBox::Critical);
		messageBox.show(); // for initialization of messageBox.size()
		messageBox.hide();
		messageBox.move(pos().x() + (width() / 2) - messageBox.width() / 2, pos().y() + height() / 2 - messageBox.height() / 2);
		messageBox.exec();
	} else {
		setDisabled(true);
		server.signIn(userName, password);
	}
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
