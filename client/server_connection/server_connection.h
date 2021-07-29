#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <QString>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QCryptographicHash>

#include "multiple_responses_types.h"
#include "requests_types.h"
#include "responses_codes.h"


class ServerConnection: public QObject
{
	Q_OBJECT

public:
	void sendLogInRequest(QString username, QString password) noexcept;
	void sendSignUpRequest(QString email, QString username, QString password) noexcept;

	static ServerConnection &getInstance() noexcept;
	ServerConnection(ServerConnection const&) = delete;
	void operator=(ServerConnection const&) = delete;

signals:
	void gotLogInResponseSignal(int resultCode);
	void gotSignUpResponseSignal(int resultCode);

private:
	ServerConnection() noexcept;
	QTcpSocket socket;

	bool send(QJsonObject &jsonObject) noexcept; // send the given json to the ServerConnection
	QString hashData(const QString &data) noexcept;

	void processData() noexcept;
	void processLogInResponse(const QJsonObject &jsonObject) noexcept;
	void processSignUpResponse(const QJsonObject &jsonObject) noexcept;

	RequestsTypes neededResponseTypes;
};

#endif // SERVER_CONNECTION_H
