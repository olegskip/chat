#include "informative_dialog.h"

void showInformativeDialog(QString title, QString text, QRect parentGeometry) noexcept
{
	QMessageBox messageBox;
	messageBox.setWindowTitle(title);
	messageBox.setStandardButtons(QMessageBox::Ok);
	messageBox.setText(text);
	messageBox.setIcon(QMessageBox::Critical);
	messageBox.show(); // for messageBox.size() initialization
	messageBox.hide();
	messageBox.move(parentGeometry.x() + (parentGeometry.width() / 2) - messageBox.width() / 2,
					parentGeometry.y() + parentGeometry.height() / 2 - messageBox.height() / 2);
	messageBox.exec();
}
