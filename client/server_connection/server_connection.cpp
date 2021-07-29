#include "server_connection.h"

ServerConnection::ServerConnection() noexcept
{
	socket.connectToHost("localhost", 6789);

	connect(&socket, &QTcpSocket::readyRead, this, &ServerConnection::processData);
}

void ServerConnection::sendLogInRequest(QString username, QString password) noexcept
{
	QJsonObject jsonObject;
	jsonObject["type"] = QString::fromStdString(convertRequestTypeToString(RequestsTypes::LOG_IN));
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	send(jsonObject);
}

void ServerConnection::sendSignUpRequest(QString email, QString username, QString password) noexcept
{
	QJsonObject jsonObject;
	jsonObject["type"] = QString::fromStdString(convertRequestTypeToString(RequestsTypes::SIGN_UP));
	jsonObject["email"] = email;
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	send(jsonObject);
}

ServerConnection &ServerConnection::getInstance() noexcept
{
	static ServerConnection instance;
	return instance;
}

bool ServerConnection::send(QJsonObject &jsonObject) noexcept
{
	// data is transmitted like length{json}, because two different messages can be delivered as one joined
	const QString jsonString = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);

	if(!jsonString.trimmed().isEmpty()) {
		socket.write(QString(QString::number(jsonString.size()) + jsonString).toUtf8());
		return true;
	}

	return false;
}

QString ServerConnection::hashData(const QString &data) noexcept
{
	return QString(QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha3_512).toHex());
}

void ServerConnection::processData() noexcept
{
	const QByteArray dataReceived = socket.readAll();
	qDebug() << "data received = " << dataReceived;
	QJsonObject jsonObject;
	jsonObject = QJsonDocument::fromJson(dataReceived).object();
	const QString packetType = jsonObject["type"].toString();
	if(packetType == QString::fromStdString(convertRequestTypeToString(RequestsTypes::LOG_IN)) &&
			doesEnumHaveState(neededResponseTypes, RequestsTypes::LOG_IN))
		processLogInResponse(jsonObject);
	else if(packetType == QString::fromStdString(convertRequestTypeToString(RequestsTypes::SIGN_UP)) &&
			doesEnumHaveState(neededResponseTypes, RequestsTypes::SIGN_UP))
		processSignUpResponse(jsonObject);
}

void ServerConnection::processLogInResponse(const QJsonObject &jsonObject) noexcept
{
	removeStateFromEnum(neededResponseTypes, RequestsTypes::LOG_IN);
	emit gotLogInResponseSignal(jsonObject["code"].toString().toInt());
}

void ServerConnection::processSignUpResponse(const QJsonObject &jsonObject) noexcept
{
	addStateToEnum(neededResponseTypes, RequestsTypes::SIGN_UP);
	emit gotSignUpResponseSignal(jsonObject["code"].toString().toInt());
}

