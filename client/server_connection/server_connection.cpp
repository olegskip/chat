#include "server_connection.h"

ServerConnection::ServerConnection() noexcept
{
	socket.connectToHost("localhost", 6789);

	connect(&socket, &QTcpSocket::readyRead, this, &ServerConnection::processData);
}

void ServerConnection::sendLogInRequest(const QString &username, const QString &password) noexcept
{
	expectedResponse = RequestsTypes::LOG_IN;

	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(expectedResponse);
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	send(jsonObject);
}

void ServerConnection::sendSignUpRequest(const QString &username, const QString &password) noexcept
{
	expectedResponse = RequestsTypes::SIGN_UP;

	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(expectedResponse);
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	send(jsonObject);
}

void ServerConnection::postNewMessage(const QString &messageText) noexcept
{
	expectedResponse = RequestsTypes::NEW_MESSAGES;

	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(expectedResponse);
	jsonObject["message"] = messageText;

	send(jsonObject);
}

void ServerConnection::sendLoadMoreMessagesRequest() noexcept
{
	if(!isLoadMoreMessagesEnabled)
		return;

	expectedResponse = RequestsTypes::NEW_MESSAGES;

	QJsonObject jsonObject;
	jsonObject["type"] = static_cast<int>(RequestsTypes::LOAD_MORE_MESSAGES);

	send(jsonObject);
	isLoadMoreMessagesEnabled = false;
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
	else if(expectedResponse == RequestsTypes::NEW_MESSAGES) {
		qDebug() << "expectedResponse = " << static_cast<int>(expectedResponse);
		if(packetType == static_cast<int>(RequestsTypes::NEW_MESSAGES))
			processNewMessages(jsonObject);
		else if(packetType == static_cast<int>(RequestsTypes::LOAD_MORE_MESSAGES))
			processLoadMoreMessagesResponse(jsonObject);
	}
}

void ServerConnection::processLogInResponse(const QJsonObject &jsonObject) noexcept
{
	emit gotLogInResponseSignal(jsonObject["username"].toString(), jsonObject["code"].toInt());
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
	if(messages.empty())
		return;

	for(const auto &messageJson: messagesJsonArray) {
		messages.push(std::shared_ptr<const Message>(new Message(messageJson["sender"].toString(), messageJson["text"].toString())));
	}
	emit gotNewMessagesSignal(messages);
}

void ServerConnection::processLoadMoreMessagesResponse(const QJsonObject &jsonObject)
{	
	const auto messagesJsonArray = jsonObject["messages"].toArray();
	if(jsonObject["code"] == static_cast<int>(ResponsesCodes::THERE_ARE_NO_MORE_MESSAGES_CANT_LOAD_MORE) ||
			jsonObject["code"] != static_cast<int>(ResponsesCodes::SUCCESSFULLY_LOADED_MORE_MESSAGES) || messagesJsonArray.empty()) {
		isLoadMoreMessagesEnabled = false;
		return;
	}
	isLoadMoreMessagesEnabled = true;

	MessagesPtrQueue messages;
	for(const auto &messageJson: messagesJsonArray) {
		messages.push(std::shared_ptr<const Message>(new Message(messageJson["sender"].toString(), messageJson["text"].toString())));
	}
	emit gotLoadMoreMessagesResponseSignal(messages);
}
