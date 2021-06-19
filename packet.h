#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include <functional>
#include <exception>
#include <tuple>
#include <memory>
#include <iostream>

#include <boost/property_tree/json_parser.hpp>


class PacketExpection: public std::exception
{
public:
	const char* what() const noexcept override
	{
		return whatMessage.c_str();
	}

protected:
	PacketExpection(std::string whatMessage_)
	{
		whatMessage = whatMessage_;
	}
	std::string whatMessage = "";
};

/*
 * For some reason, the program may receive less han it should
 * If the length is greater than it should be, the program calls the NotFinishedPacketException
 * Read the NotFinishedPacketException comment
 */
class InvalidPacketLengthException: public PacketExpection
{
public:
	InvalidPacketLengthException(std::string packetData): 
		PacketExpection("There is no proper packet length. Packet must be: length{json}. Data = " + packetData) {}
};


// class NotFinishedPacketException: public PacketExpection
// {
// public:
// 	NotFinishedPacketException(std::string packetData): 
// 		PacketExpection("Waiting for the end. Data = " + packetData), packetData(packetData_) {}

// 	const std::string packetData_;
// };


class IncompletePacket
{
public:
	IncompletePacket(std::string data_, size_t expectedLength_);

	IncompletePacket operator+(const IncompletePacket &incompletePacket);

	bool isComplete() const;

	const std::string data;
	const size_t expectedLength;
};

/*
 * Data is transmitted as:
 * data_length{json}
 * because several different messages can be delivered as one message
 */

class Packet
{
public:
	Packet(std::string data_);
	Packet(const IncompletePacket &packet);

	// size_t getLength() const;
	const std::string &getData() const;
	bool getIsComplete() const;
	const boost::property_tree::ptree &getJsonTree() const;

	// One received message can contain a lot of packets, this function split them all
	// static std::vector<std::shared_ptr<Packet>> splitPackets(std::string packetsString, size_t incompletePacketLength);


private:
	void convertDataToJson();

	// size_t length = 0;
	std::string data;
	boost::property_tree::ptree jsonTree;
	bool isAnswered = false;
	bool isComplete = false;
};


#endif