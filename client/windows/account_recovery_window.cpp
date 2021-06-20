#include "account_recovery_window.h"

AccountRecoveryWindow::AccountRecoveryWindow(QWidget *parent): QWidget(parent)
{
	setLayout(&mainLayout);

	emailInput.setParent(this);
	emailInput.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	emailInput.setPlaceholderText("email");
	mainLayout.addWidget(&emailInput, 30);

	usernameInput.setParent(this);
	usernameInput.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	usernameInput.setPlaceholderText("username");
	mainLayout.addWidget(&usernameInput, 30);

	backButton.setParent(this);
	backButton.setText("← Back");
	backButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&backButton, &QPushButton::clicked, this, &AccountRecoveryWindow::showSignInWindowSignal);
	buttonsLayout.addWidget(&backButton);

	recoverButton.setParent(this);
	recoverButton.setText("Recover →");
	recoverButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	buttonsLayout.addWidget(&recoverButton);

	mainLayout.addLayout(&buttonsLayout);
}
