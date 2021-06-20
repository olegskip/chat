#ifndef PACKETS_MANAGER_H
#define PACKETS_MANAGER_H

#include "packet.h"


class PacketsManager
{
public:
	PacketsManager();

	void splitPackets(std::string packetsString);
	const std::vector<std::shared_ptr<boost::property_tree::ptree>> getPacketsJson();
	void clearReadyPackets();


private:
	std::vector<std::shared_ptr<Packet>> readyPackets;
	std::unique_ptr<IncompletePacket> incompletePacket;

	std::pair<size_t, size_t> findLengthSignPos(std::string str);
	void addReadyPacket(std::string str); // this function is added, because a packet can have not valid json
};

#endif