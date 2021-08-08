#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QTcpSocket>

#include <memory>

#include "requests_types.h"
#include "responses_codes.h"
#include "message.h"

class ServerConnection: public QObject
{
	Q_OBJECT

public:
	void sendLogInRequest(const QString &username, const QString &password) noexcept;
	void sendSignUpRequest(const QString &username, const QString &password) noexcept;
	void postNewMessage(const QString &messageText) noexcept;
	void sendLoadMoreMessagesRequest() noexcept;

	static ServerConnection &getInstance() noexcept;
	ServerConnection(ServerConnection const&) = delete;
	void operator=(ServerConnection const&) = delete;
	static QString hashData(const QString &data) noexcept;

	void startProcessingMessages() noexcept;

signals:
	void gotLogInResponseSignal(QString username, int resultCode);
	void gotSignUpResponseSignal(int resultCode);
	void gotNewMessagesSignal(MessagesPtrQueue messages);
	void gotLoadMoreMessagesResponseSignal(MessagesPtrQueue messages);

private:
	ServerConnection() noexcept;
	QTcpSocket socket;

	bool send(QJsonObject &jsonObject) noexcept; // send the given json to the ServerConnection

	void processData() noexcept;
	void processLogInResponse(const QJsonObject &jsonObject) noexcept;
	void processSignUpResponse(const QJsonObject &jsonObject) noexcept;
	void processNewMessages(const QJsonObject &jsonObject) noexcept;
	void processLoadMoreMessagesResponse(const QJsonObject &jsonObject);

	bool isLoadMoreMessagesEnabled = true;
	RequestsTypes expectedResponse;
};

#endif // SERVER_CONNECTION_H
