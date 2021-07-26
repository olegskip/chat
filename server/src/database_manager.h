#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <iostream>
#include <memory>
#include <mariadb/conncpp.hpp>
#include <boost/format.hpp>


class DatabaseManager
{
public:
	static DatabaseManager &getInstance() noexcept;
	DatabaseManager(DatabaseManager const&) = delete;
	void operator=(DatabaseManager const&) = delete;

	bool checkSignIn(std::string username, std::string password) noexcept;

private:
	DatabaseManager() noexcept;

	// sql classes have private destructors, so I can't use smart pointers
	std::unique_ptr<sql::Driver> driver;
	std::unique_ptr<sql::Connection> connection;
	std::unique_ptr<sql::Statement> statement;
	std::unique_ptr<sql::ResultSet> result;
};

#endif // DATABASE_MANAGER_H
