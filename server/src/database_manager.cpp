#include "database_manager.h"

DatabaseManager::DatabaseManager() noexcept
{
	try {
		driver.reset(sql::mariadb::get_driver_instance());
		sql::SQLString url = sql::SQLString("tcp://192.168.1.251:3306");
		connection.reset(driver->connect(url, sql::SQLString("chat_user"), sql::SQLString("chat_user")));
		connection->setSchema("chat");
	}
	catch (sql::SQLException &e) {
		std::cerr << e.what() << std::endl;
		exit(-1);
	}
}

bool DatabaseManager::doesUserExist(const std::string &username) noexcept
{
	std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement("SELECT EXISTS(SELECT * FROM accounts WHERE username = ?)"));
	statement->setString(1, username);
	std::unique_ptr<sql::ResultSet> result(statement->executeQuery());
	result->next();
	
	return result->getBoolean(1);
}

bool DatabaseManager::checkLogIn(const std::string &username, const std::string &password) noexcept
{
	std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement("SELECT EXISTS(SELECT * FROM accounts WHERE username = ? AND password = ?)"));
	statement->setString(1, username);
	statement->setString(2, password);
	std::unique_ptr<sql::ResultSet> result(statement->executeQuery());
	result->next();

	return result->getBoolean(1);
}

void DatabaseManager::forceToAddUser(const std::string &email, const std::string &username, const std::string password) noexcept
{
	std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement("INSERT INTO accounts(email, username, password) VALUES(?, ?, ?)"));
	statement->setString(1, email);
	statement->setString(2, username);
	statement->setString(3, password);
	statement->execute();
}

DatabaseManager &DatabaseManager::getInstance() noexcept // static
{
	static DatabaseManager instance;
	return instance;
}
