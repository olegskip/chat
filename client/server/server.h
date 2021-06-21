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

	static Server &getInstance();
	Server(Server const&) = delete;
	void operator= (Server const&) = delete;

signals:
	void signInResponse(QString username, bool result);

private:
	Server();
	QTcpSocket socket;

	bool send(QJsonObject &jsonObject);
	QString hashData(const QString &data);

	void processData();
	void processSignIn(const QJsonObject &jsonObject);

	size_t requestID;
};

#endif // SERVER_H
