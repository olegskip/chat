#include "start_window.h"

StartWindow::StartWindow(QWidget *parent): QWidget(parent)
{
	setLayout(&buttonsLayout);

	createNewAccountButton.setParent(this);
	createNewAccountButton.setText("Create a new account");
	createNewAccountButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	buttonsLayout.addWidget(&createNewAccountButton);

	signInButton.setParent(this);
	signInButton.setText("Sign in");
	signInButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&signInButton, &QPushButton::clicked, this, &StartWindow::openSignInWindow);
	buttonsLayout.addWidget(&signInButton);
}

void StartWindow::openSignInWindow()
{
	signInWindow.reset(new SignInWindow());
	signInWindow->resize(size());
	signInWindow->move(pos());
	signInWindow->show();

	connect(signInWindow.get(), &SignInWindow::showStartWindowSignal, [this]()
	{
		resize(signInWindow->size());
		move(signInWindow->pos());
		signInWindow->hide();
		show();

	});
	hide();
}

StartWindow::~StartWindow()
{
}

