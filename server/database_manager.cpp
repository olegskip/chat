#include "database_manager.h"

DatabaseManager::DatabaseManager()
{
	try {
		driver = get_driver_instance();
		connection = driver->connect("tcp://192.168.1.251:3306", "admin", "admin");
		connection->setSchema("chat");
		statement = connection->createStatement();
	}
	catch (sql::SQLException &e) {
		std::cerr << e.what() << std::endl;
		exit(-1);
	}
}

bool DatabaseManager::checkSignIn(std::string username, std::string password)
{
	// std::cout << "query = " << std::string(boost::str(boost::format("SELECT EXISTS(SELECT * FROM accounts WHERE username = '%1%' AND password = '%2%');") % username % password)) << std::endl;
	result = statement->executeQuery(std::string(boost::str(boost::format("SELECT EXISTS(SELECT * FROM accounts WHERE username = '%1%'" 
		"AND password = '%2%');") % username % password)));
	
	if(result->next())
		return result->getBoolean(1);
	return false;
}

DatabaseManager &DatabaseManager::getInstance() // static
{
	static DatabaseManager instance;
	return instance;
}