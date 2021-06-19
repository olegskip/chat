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

// Some packets may be too long, so they can be split to several different messages
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

	const std::string &getData() const;
	const boost::property_tree::ptree &getJsonTree() const;
	bool getIsJsonValid() const;

private:
	bool convertDataToJson();

	std::string data;
	boost::property_tree::ptree jsonTree;
	bool isAnswered = false;
	bool isJsonValid = false;

	// these field will be filled with json data
	std::string ID = "";
	std::string type = "";


};


#endif