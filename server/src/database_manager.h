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

	bool doesUserExist(const std::string &username) noexcept;
	bool checkLogIn(const std::string &username, const std::string &password) noexcept;
	void forceToAddUser(const std::string &email, const std::string &username, const std::string password) noexcept;

private:
	DatabaseManager() noexcept;

	std::unique_ptr<sql::Driver> driver;
	std::unique_ptr<sql::Connection> connection;
	// std::unique_ptr<sql::Statement> statement;
	// std::unique_ptr<sql::ResultSet> result;
};

#endif // DATABASE_MANAGER_H
