#ifndef SESSION_H
#define SESSION_h

#include <boost/asio.hpp>
#include <thread>
#include <boost/signals2.hpp>

#include "packets_manager.h"


using boost::asio::ip::tcp;

class Session: public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket);

private:

	/*
	 * The function reads all the information from the socket,
	 * then it splits and converts the data via the Packet class
	 * and gives one by one to the processPacket function 
	 */
	void readData();
	void processPacket(std::shared_ptr<Packet> packet);

	PacketsManager packetsManager;
 
	tcp::socket sessionSocket;

	// boost::signals2::signal<void(char, size_t)> dataReceived;
	
	
	/*
	 * Boost works better with its buffer, but it's more convenient to work with std::string,
	 * they both contain littely contains the same data, but in different types
	 */
	boost::asio::streambuf buffer;
	std::string dataString;
};


#endif