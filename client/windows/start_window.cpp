#include "start_window.h"

StartWindow::StartWindow(QWidget *parent) noexcept
	: QWidget(parent)
{
	setLayout(&buttonsLayout);

	signUpButton.setParent(this);
	signUpButton.setText("Sign up");
	signUpButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&signUpButton, &QPushButton::clicked, this, &StartWindow::showSignUpWindow);
	buttonsLayout.addWidget(&signUpButton);

	logInButton.setParent(this);
	logInButton.setText("Log in");
	logInButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&logInButton, &QPushButton::clicked, this, &StartWindow::showLogInWindow);
	buttonsLayout.addWidget(&logInButton);
}

void StartWindow::showSignUpWindow() noexcept
{
	signUpWindow.reset(new SignUpWindow());
	signUpWindow->show();
	signUpWindow->setGeometry(geometry());
	connect(signUpWindow.get(), &SignUpWindow::goBackSignal, this, [this]()
	{
		show();
		setGeometry(signUpWindow->geometry());
		signUpWindow->hide();
	});
	hide();
}

void StartWindow::showLogInWindow() noexcept
{
	logInWindow.reset(new LogInWindow());
	logInWindow->show();
	logInWindow->setGeometry(geometry());
	connect(logInWindow.get(), &LogInWindow::goBackSignal, this, [this]()
	{
		show();
		setGeometry(logInWindow->geometry());
		logInWindow->hide();

	});
	hide();
}

StartWindow::~StartWindow() noexcept
{
}

