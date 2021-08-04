#include "server_connection.h"

ServerConnection::ServerConnection() noexcept
{
	socket.connectToHost("localhost", 6789);

	connect(&socket, &QTcpSocket::readyRead, this, &ServerConnection::processData);
}

void ServerConnection::sendLogInRequest(const QString &username, const QString &password) noexcept
{
	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(RequestsTypes::LOG_IN);
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	expectedResponse = RequestsTypes::LOG_IN;
	send(jsonObject);
}

void ServerConnection::sendSignUpRequest(const QString &username, const QString &password) noexcept
{
	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(RequestsTypes::SIGN_UP);
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	expectedResponse = RequestsTypes::SIGN_UP;
	send(jsonObject);
}

void ServerConnection::postNewMessage(const QString &messageText) noexcept
{
	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(RequestsTypes::NEW_MESSAGES);
	jsonObject["message"] = messageText;

	expectedResponse = RequestsTypes::NEW_MESSAGES;
	send(jsonObject);
}

ServerConnection &ServerConnection::getInstance() noexcept
{
	static ServerConnection instance;
	return instance;
}

QString ServerConnection::hashData(const QString &data) noexcept
{
	return QString(QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha3_512).toHex());
}

void ServerConnection::startProcessingMessages() noexcept
{
	expectedResponse = RequestsTypes::NEW_MESSAGES;
}

bool ServerConnection::send(QJsonObject &jsonObject) noexcept
{
	// data is transmitted like length{json}, because two different messages can be delivered as one joined
	const QString jsonString = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
	qDebug() << "send = " << jsonString;
	if(!jsonString.trimmed().isEmpty()) {
		socket.write(QString(QString::number(jsonString.size()) + jsonString).toUtf8());
		return true;
	}

	return false;
}

void ServerConnection::processData() noexcept
{
	if(expectedResponse == RequestsTypes::NOTHING)
		return;

	const QByteArray dataReceived = socket.readAll();
	qDebug() << "data received = " << dataReceived;
	QJsonObject jsonObject;
	jsonObject = QJsonDocument::fromJson(dataReceived).object();
	const int packetType = jsonObject["type"].toInt();
	if(packetType == static_cast<int>(RequestsTypes::LOG_IN) && expectedResponse == RequestsTypes::LOG_IN)
		processLogInResponse(jsonObject);
	else if(packetType == static_cast<int>(RequestsTypes::SIGN_UP) && expectedResponse == RequestsTypes::SIGN_UP)
		processSignUpResponse(jsonObject);
	else if(packetType == static_cast<int>(RequestsTypes::NEW_MESSAGES) && expectedResponse == RequestsTypes::NEW_MESSAGES)
		processNewMessages(jsonObject);

}

void ServerConnection::processLogInResponse(const QJsonObject &jsonObject) noexcept
{
	emit gotLogInResponseSignal(jsonObject["code"].toInt());
}

void ServerConnection::processSignUpResponse(const QJsonObject &jsonObject) noexcept
{
	expectedResponse = RequestsTypes::NOTHING;
	emit gotSignUpResponseSignal(jsonObject["code"].toInt());
}

void ServerConnection::processNewMessages(const QJsonObject &jsonObject) noexcept
{
	const auto messagesJsonArray = jsonObject["messages"].toArray();

	MessagesPtrQueue messages;
	for(const auto &messageJson: messagesJsonArray) {
		messages.push(std::shared_ptr<const Message>(new Message(messageJson["sender"].toString(), messageJson["text"].toString())));
	}
	emit gotNewMessagesSignal(messages);
}
