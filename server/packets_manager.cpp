#include "packets_manager.h"

PacketsManager::PacketsManager()
{

}

void PacketsManager::splitPackets(std::string packetsString)
{
	if(packetsString.empty()) 
		return;

	auto findLengthSignPos = [](std::string str) -> std::pair<size_t, size_t>
	{
		size_t lengthStartPos = 0, lengthEndPos = 0;

		for(size_t i = 0; i < str.size(); ++i) {
			if(isdigit(str[i])) {
				if(lengthStartPos != 0)
					lengthStartPos = i;
			}
			else {
				lengthEndPos = i - 1;
				break;
			}
		}
		return {lengthStartPos, lengthEndPos};
	};

	if(incompletePacket) {
		// if there is a incomplete packet, then the programm should look for the end of the current incomplete packet
		const size_t lengthToBecomeReady = incompletePacket->expectedLength - incompletePacket->data.size();

		if(lengthToBecomeReady > packetsString.size()) {
			// then there should be another message with the end of the packet
			incompletePacket = std::make_unique<IncompletePacket>(*incompletePacket.get() + IncompletePacket(packetsString, 0));
			return;
		}
		else {
			// then the incompletePacket is complete
			incompletePacket = std::make_unique<IncompletePacket>(*incompletePacket.get() + 
				IncompletePacket(packetsString.substr(0, lengthToBecomeReady), 0));
			packetsString.erase(packetsString.begin(), packetsString.begin() + lengthToBecomeReady);
			readyPackets.push_back(std::make_unique<Packet>(*incompletePacket.get()));
			incompletePacket.reset();
			splitPackets(packetsString);
			return;
		}

		// if the incompletePacket is complete, it is ready to be processed
		if(incompletePacket->isComplete()) {
			readyPackets.push_back(std::make_unique<Packet>(*incompletePacket));
			incompletePacket.reset();
			splitPackets(packetsString);
		}

	}
	else {
		size_t lengthStartPos = 0, lengthEndPos = 0;
		std::tie(lengthStartPos, lengthEndPos) = findLengthSignPos(packetsString);
		// std::cout << "substr = " << packetsString.substr(lengthStartPos, lengthEndPos - lengthStartPos + 1) << std::endl;
		const size_t packetLength = std::stoi(packetsString.substr(lengthStartPos, lengthEndPos - lengthStartPos + 1));

		if(packetLength > packetsString.size()) {
			// then the program should look for the ending in the next message, so the packet is incomplete
			incompletePacket = std::make_unique<IncompletePacket>(std::string(packetsString.begin() + lengthEndPos + 1, packetsString.end()), 
				packetLength);
			return;
		}
		else {
			// then the packet is complete and the program can process it
			readyPackets.push_back(std::make_unique<Packet>(packetsString.substr(lengthEndPos + 1, 
				lengthEndPos - lengthStartPos + 1 + packetLength)));
			packetsString.erase(packetsString.begin() + lengthStartPos, packetsString.begin() + lengthEndPos - lengthStartPos + 1 + packetLength);
			splitPackets(packetsString);
		}
	}
}
