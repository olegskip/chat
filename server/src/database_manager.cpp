#include "database_manager.h"

DatabaseManager::DatabaseManager() noexcept
{
	try {
		driver.reset(sql::mariadb::get_driver_instance());
		sql::SQLString url = sql::SQLString("tcp://192.168.1.251:3306");
		connection.reset(driver->connect(url, sql::SQLString("chat_user"), sql::SQLString("chat_user")));
		connection->setSchema("chat");
		statement.reset(connection->createStatement());
	}
	catch (sql::SQLException &e) {
		std::cerr << e.what() << std::endl;
		exit(-1);
	}
}

bool DatabaseManager::checkSignIn(std::string username, std::string password) noexcept
{
	result.reset(statement->executeQuery(std::string(boost::str(boost::format("SELECT EXISTS(SELECT * FROM accounts WHERE username = '%1%'" 
		"AND password = '%2%');") % username % password))));
	
	if(result->next())
		return result->getBoolean(1);
	return false;
}

DatabaseManager &DatabaseManager::getInstance() noexcept // static
{
	static DatabaseManager instance;
	return instance;
}
