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
	signUpWindow->resize(size());
	signUpWindow->move(pos());
	signUpWindow->show();

	connect(signUpWindow.get(), &SignUpWindow::goBackSignal, this, [this]()
	{
		resize(signUpWindow->size());
		move(signUpWindow->pos());
		signUpWindow->hide();
		show();

	});
	hide();
}

void StartWindow::showLogInWindow() noexcept
{
	logInWindow.reset(new LogInWindow());
	logInWindow->resize(size());
	logInWindow->move(pos());
	logInWindow->show();

	connect(logInWindow.get(), &LogInWindow::goBackSignal, this, [this]()
	{
		resize(logInWindow->size());
		move(logInWindow->pos());
		logInWindow->hide();
		show();

	});
	hide();
}

StartWindow::~StartWindow() noexcept
{
}

