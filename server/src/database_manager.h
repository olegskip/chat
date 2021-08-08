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
	void addMessage(const Message &message) noexcept;

	/*
	 * if numberOfMessages is greater than the actual number of messages, the function returns as many as possible
	 * Returns messages located at [lastMessageId - newMessagesQuantity(in message.h), newMessagesQuantity(in message.h)]
	 */ 
	MessagesPtrQueue getOldMessages(unsigned int lastMessageId) noexcept;

	unsigned int getMessagesQuantity() const noexcept;

private:
	DatabaseManager() noexcept;

	std::unique_ptr<sql::Driver> driver;
	std::unique_ptr<sql::Connection> connection;
	std::unique_ptr<sql::Statement> statement;
	std::unique_ptr<sql::ResultSet> result;

	unsigned int messagesQuantity = 0;
	unsigned int countMessage() noexcept;
};

#endif // DATABASE_MANAGER_H
