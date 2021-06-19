#ifndef ACCOUNT_RECOVERY_WINDOW_H
#define ACCOUNT_RECOVERY_WINDOW_H

#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


class AccountRecoveryWindow: public QWidget
{
	Q_OBJECT

public:
	explicit AccountRecoveryWindow(QWidget *parent = nullptr);

signals:
	void showSignInWindowSignal();

private:
	QVBoxLayout mainLayout;
	QHBoxLayout buttonsLayout;

	QLineEdit emailInput;
	QLineEdit usernameInput;

	QPushButton backButton;
	QPushButton recoverButton;
};

#endif
