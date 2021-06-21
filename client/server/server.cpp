#include "server.h"

Server::Server()
{
	socket.connectToHost("localhost", 6789);
}

void Server::signIn(QString username, QString password)
{
	QJsonObject jsonObject;
	jsonObject["type"] = "sign_in";
	jsonObject["username"] = username;
	jsonObject["password"] = hashData(password);

	send(jsonObject);

	connect(&socket, &QTcpSocket::readyRead, this, &Server::processData);
}

Server &Server::getInstance()
{
	static Server instance;
	return instance;
}

bool Server::send(QJsonObject &jsonObject)
{
	// every sended message has own id: c_n(stands for client_number) or for client and s_n (stands for server_number)
	jsonObject["id"] = QString("c_" +QString::number(requestID++));

	// data is transmitted like length{json}, because two different messages can be delivered as one joined
	const QString jsonString = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);

	if(!jsonString.trimmed().isEmpty()) {
		socket.write(QString(QString::number(jsonString.size()) + jsonString).toUtf8());
		return true;
	}

	return false;
}

QString Server::hashData(const QString &data)
{
	return QString(QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha3_512).toHex());
}

void Server::processData()
{
	const QByteArray dataReceived = socket.readAll();
	qDebug() << "data received = " << dataReceived;
	QJsonObject jsonObject;
	jsonObject = QJsonDocument::fromJson(dataReceived).object();
	const QString packetType = jsonObject["type"].toString();
	if(packetType == "sign_in")
		processSignIn(jsonObject);
}

void Server::processSignIn(const QJsonObject &jsonObject)
{
	emit signInResponse(jsonObject["username"].toString(), jsonObject["result"].toString().toInt());
}
