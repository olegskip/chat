#include "message_box.h"

MessageBox::MessageBox(QString title, QString text, QRect parentGeometry) noexcept
{
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
