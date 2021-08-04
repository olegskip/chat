#include "packet.h"

// ————— IncompletePacket —————
IncompletePacket::IncompletePacket(std::string data_, size_t expectedLength_) noexcept
	:data(data_), expectedLength(expectedLength_)
{

}

IncompletePacket IncompletePacket::operator+(const IncompletePacket &incompletePacket) noexcept
{
	return IncompletePacket(data + incompletePacket.data, expectedLength);
}

bool IncompletePacket::isComplete() const noexcept
{
	return data.size() == expectedLength;
}

// ————— Packet —————
Packet::Packet(std::string data_) noexcept
{
	data = data_;

	isJsonValid = convertDataToJson();
}

Packet::Packet(const IncompletePacket &packet) noexcept
{
	data = packet.data;
	isJsonValid = convertDataToJson();
}

const std::string &Packet::getData() const noexcept
{
	return data;
}

const std::shared_ptr<const nlohmann::json> Packet::getJsonTree() const noexcept
{
	return json;
}

bool Packet::getIsJsonValid() const noexcept
{
	return isJsonValid;
}

bool Packet::convertDataToJson() noexcept
{
	try {
		json = std::make_shared<nlohmann::json>(nlohmann::json::parse(data));
		return true;
	}
	catch(const nlohmann::json::parse_error &e) {
		std::cerr << "Cannot parse json. Error = " << e.what() << std::endl;
		return false;
	} 
	
}
