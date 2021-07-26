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
	IncompletePacket(std::string data_, size_t expectedLength_) noexcept;

	IncompletePacket operator+(const IncompletePacket &incompletePacket) noexcept;

	bool isComplete() const noexcept;

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
	Packet(std::string data_) noexcept;
	Packet(const IncompletePacket &packet) noexcept;

	const std::string &getData() const noexcept;
	const std::shared_ptr<boost::property_tree::ptree> getJsonTree() const noexcept;
	bool getIsJsonValid() const noexcept;

private:
	bool convertDataToJson() noexcept;

	std::string data;
	std::shared_ptr<boost::property_tree::ptree> jsonTree = std::make_shared<boost::property_tree::ptree>();
	bool isAnswered = false;
	bool isJsonValid = false;

	// these field will be filled with json data
	std::string id = "";
	std::string type = "";
};

#endif // SESSION_H
