#ifndef PACKETS_MANAGER_H
#define PACKETS_MANAGER_H

#include "packet.h"


class PacketsManager
{
public:
	PacketsManager();

	void splitPackets(std::string packetsString);


private:
	std::vector<std::shared_ptr<Packet>> readyPackets;

	std::unique_ptr<IncompletePacket> incompletePacket;
};

#endif