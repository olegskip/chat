#ifndef SESSION_H
#define SESSION_h

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <boost/algorithm/string.hpp>

#include <mutex>

#include "packets_manager.h"
#include "database_manager.h"
#include "requests_types.h"
#include "responses_codes.h"

using boost::asio::ip::tcp;

class Session: public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, boost::asio::io_service &ioService) noexcept;
	~Session() noexcept;

	boost::signals2::signal<void(std::shared_ptr<const Message> message)> newMessagePostedSignal;
	boost::signals2::signal<void()> disconnectSignal;

	void addNewMessageToQueue(std::shared_ptr<const Message> &message) noexcept;

private:
	/*
	 * The function reads all the information from the socket,
	 * then it splits and converts the data via the Packet class
	 * and gives one by one to the processPacket function 
	 */
	void readData() noexcept;

	void operateRequest(std::shared_ptr<const nlohmann::json> &requestJson) noexcept;
	void processLogInRequest(const std::string &username, const std::string &password) noexcept;
	void processSignUpRequest(const std::string &username, const std::string &password) noexcept;
	void processPostMessageRequest(const std::string &messageText) noexcept;
	void proccessLoadMoreMessagesRequest() noexcept;
	PacketsManager packetsManager;
 
	tcp::socket sessionSocket;

	/*
	 * Boost works better with its buffer, but it's more convenient to work with std::string,
	 * they both contain the same data, but in different types
	 */
	boost::asio::streambuf buffer;
	std::string dataString;

	std::string username = "";
	int oldestMessageVisibleId = -1;
	MessagesPtrQueue newMessagesToSendQueue;
	boost::asio::deadline_timer sendNewMessagesTimer;
	const boost::posix_time::millisec sendNewMessagesTimerInterval = boost::posix_time::millisec(100); // milisecs
	bool isSendNewMessagesTimerWorking = false;
	std::mutex sendNewMessagesTimerMutex;
	void startSendNewMessagesTimer() noexcept;
	void sendMessagesFromQueue() noexcept;

	void sendJson(const nlohmann::json &json) noexcept;

	DatabaseManager &databaseManager = DatabaseManager::getInstance();
};

#endif // SESSION_h
