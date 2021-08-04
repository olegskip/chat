#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <iostream>
#include <memory>
#include <mariadb/conncpp.hpp>
#include <boost/format.hpp>

#include "message.h"


class DatabaseManager
{
public:
	static DatabaseManager &getInstance() noexcept;
	~DatabaseManager() noexcept;
	DatabaseManager(DatabaseManager const&) = delete;
	void operator=(DatabaseManager const&) = delete;

	bool doesUserExist(const std::string &username) noexcept;
	bool checkLogIn(const std::string &username, const std::string &password) noexcept;
	void forceToAddUser(const std::string &username, const std::string password) noexcept;
	void addMessage(Message message);

	/*
	 * if numberOfMessages is greater than the actual number, the funcntion returns as many as possible
	 * Returns messages located at [endPosition - numberOfMessages, endPosition]
	 * New messages are located in the end 
	 */ 
	void getOldMessages(std::size_t endPosition, std::size_t numberOfMessages);

	/*
	 * if numberOfMessages is greater than the actual number, the funcntion returns as many as possible
	 * Returns messages located at [startFromPosition, startFromPosition + numberOfMessages]
	 * New messages are located in the end
	 */ 
	void getLastMessages(std::size_t startFromPosition, std::size_t numberOfMessages);

private:
	DatabaseManager() noexcept;

	std::unique_ptr<sql::Driver> driver;
	std::unique_ptr<sql::Connection> connection;
	std::unique_ptr<sql::Statement> statement;
	std::unique_ptr<sql::ResultSet> result;
};

#endif // DATABASE_MANAGER_H
