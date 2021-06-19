#include "server.h"

Server::Server()
{
	socket.connectToHost("localhost", 6789);
}

void Server::signIn(QString username, QString password)
{
	QJsonObject jsonObject;
	jsonObject["type"] = "sign_in";
	jsonObject["username"] = hashData(username);
	jsonObject["password"] = hashData(password);
	jsonObject["trash"] = hashData("trash") + hashData("trash");

	for(int i = 0; i < 4; ++i)
		send(jsonObject);

	connect(&socket, &QTcpSocket::readyRead, [this]()
	{
	});
}

bool Server::send(QJsonObject &jsonObject)
{
	// every sended message has own id: c_n(stands for client_number) or for client and s_n (stands for server_number)
	jsonObject["ID"] = QString("c_" +QString::number(requestID++));

	// data is transmitted like length{json}, because two different messages can be delivered as one joined
	const QString jsonString = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);

	if(!jsonString.trimmed().isEmpty()) {
		socket.write(QString(QString::number(jsonString.size()) + jsonString).toUtf8());
		return true;
	}

	return false;
}

Server &Server::getInstance()
{
	static Server instance;
	return instance;
}

QString Server::hashData(const QString &data)
{
	return QString(QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha3_512).toHex());
}
