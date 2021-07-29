#include "account_recovery_window.h"

AccountRecoveryWindow::AccountRecoveryWindow(QWidget *parent) noexcept
	: QWidget(parent)
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

	goBackButton.setParent(this);
	goBackButton.setText("← Back");
	goBackButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(&goBackButton, &QPushButton::clicked, this, &AccountRecoveryWindow::goBackSignal);
	buttonsLayout.addWidget(&goBackButton);

	recoverButton.setParent(this);
	recoverButton.setText("Recover →");
	recoverButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	buttonsLayout.addWidget(&recoverButton);

	mainLayout.addLayout(&buttonsLayout);
}
