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
	// length = length_;
	// isComplete = isComplete_;

	// std::cout << "newPacket"
	// convertDataToJson();
}

Packet::Packet(const IncompletePacket &packet)
{
	data = packet.data;
}

// size_t Packet::getLength() const
// {
// 	return length;
// }

const std::string &Packet::getData() const
{
	return data;
}

bool Packet::getIsComplete() const
{
	return isComplete;
}

// std::vector<std::shared_ptr<Packet>> Packet::splitPackets(std::string packetsString, size_t incompletePacketLength) // static
// {
// 	std::vector<std::shared_ptr<Packet>> output;

// 	auto findLengthPos = [](std::string str) -> std::pair<size_t, size_t>
// 	{
// 		size_t lengthStartPos = 0, lengthEndPos = 0;

// 		for(size_t i = 0; i < str.size(); ++i) {
// 			if(isdigit(str[i])) {
// 				if(lengthStartPos != 0)
// 					lengthStartPos = i;
// 			}
// 			else {
// 				lengthEndPos = i - 1;
// 				break;
// 			}
// 		}
// 		return {lengthStartPos, lengthEndPos};
// 	};

// 	if(!packetsString.empty() && incompletePacketLength > 0) {
// 		// std::cout << "incompletePacketLength = " << incompletePacketLength << std::endl;
// 		try {
// 			const size_t packetLength = std::min(packetsString.size(), incompletePacketLength);
// 			output.push_back(std::make_shared<Packet>(packetsString.substr(0, packetLength), packetLength, false));
// 			packetsString.erase(packetsString.begin(), packetsString.begin() + packetLength);
// 		}
// 		catch(std::exception &exception) {
// 			std::cout << "THROWING EXCEPTION EADDFDSF " << std::endl;
// 			throw InvalidPacketLengthException(packetsString + ". Exception error = " + exception.what());
// 		}
// 	}

// 	while(!packetsString.empty()) {
// 		size_t lengthStartPos = 0, lengthEndPos = 0;
// 		std::tie(lengthStartPos, lengthEndPos) = findLengthPos(packetsString);

// 		try {
// 			const std::string lengthStr = packetsString.substr(lengthStartPos, lengthEndPos - lengthStartPos + 1);
// 			const size_t length = std::stoi(lengthStr);
// 			if(length > packetsString.size() - lengthStr.size()) {
// 				const std::string packetData = packetsString.substr(lengthEndPos + 1, packetsString.size() - lengthStr.size());
// 				output.push_back(std::make_shared<Packet>(packetData, length, false));
// 				packetsString.clear();
// 			}
// 			else {
// 				const std::string packetData = packetsString.substr(lengthEndPos + 1, length);
// 				output.push_back(std::make_shared<Packet>(packetData, length));
// 				packetsString.erase(packetsString.begin(), packetsString.begin() + packetData.size() + lengthStr.size());
// 			}
// 		} 
// 		catch(std::exception &exception) {
// 			std::cout << "THROW NORMAL" << std::endl;
// 			throw InvalidPacketLengthException(packetsString + ". Exception error = " + exception.what());
// 		}
// 	}
// 	return output;
// }

const boost::property_tree::ptree &Packet::getJsonTree() const
{
	return jsonTree;
}

void Packet::convertDataToJson()
{
	std::stringstream ss;
	ss << data;
	boost::property_tree::read_json(ss, jsonTree);
}