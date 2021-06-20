#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <memory>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <boost/format.hpp>


class DatabaseManager
{
public:
	static DatabaseManager &getInstance();
	DatabaseManager(DatabaseManager const&) = delete;
	void operator= (DatabaseManager const&) = delete;

	bool checkSignIn(std::string username, std::string password);

private:
	DatabaseManager();

	// sql classes have private destructors, so I can't use smart pointers
	sql::Driver *driver;
	sql::Connection *connection;
	sql::Statement *statement;
	sql::ResultSet *result;
};

#endif