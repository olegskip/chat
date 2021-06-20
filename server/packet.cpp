#include "packet.h"

// ————— IncompletePacket —————
IncompletePacket::IncompletePacket(std::string data_, size_t expectedLength_): data(data_), expectedLength(expectedLength_)
{

}

IncompletePacket IncompletePacket::operator+(const IncompletePacket &incompletePacket)
{
	return IncompletePacket(data + incompletePacket.data, expectedLength);
}

bool IncompletePacket::isComplete() const
{
	return data.size() == expectedLength;
}

// ————— Packet —————
Packet::Packet(std::string data_)
{
	data = data_;

	isJsonValid = convertDataToJson();
}

Packet::Packet(const IncompletePacket &packet)
{
	data = packet.data;
	isJsonValid = convertDataToJson();
}

const std::string &Packet::getData() const
{
	return data;
}

const std::shared_ptr<boost::property_tree::ptree> Packet::getJsonTree() const
{
	return jsonTree;
}

bool Packet::getIsJsonValid() const
{
	return isJsonValid;
}

bool Packet::convertDataToJson()
{
	std::stringstream ss;
	ss << data;
	try {
		boost::property_tree::read_json(ss, *jsonTree.get());
		id = jsonTree->get<std::string>("id");
		type = jsonTree->get<std::string>("type");
	}
	catch (const boost::property_tree::ptree_error &e) {
		std::cout << "what = " << e.what() << std::endl;
		return false;
	}
	return true;
}