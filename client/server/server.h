#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QCryptographicHash>


class Server: public QObject
{
	Q_OBJECT

public:
	void signIn(QString username, QString password);

	bool send(QJsonObject &jsonObject);

	static Server &getInstance();
	Server(Server const&) = delete;
	void operator= (Server const&) = delete;

private:
	Server();
	QTcpSocket socket;

	QString hashData(const QString &data);

	size_t requestID;
};

#endif // SERVER_H
