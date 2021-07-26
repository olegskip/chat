#ifndef PACKETS_MANAGER_H
#define PACKETS_MANAGER_H

#include "packet.h"


class PacketsManager
{
public:
	PacketsManager() noexcept;

	void splitPackets(std::string packetsString) noexcept;
	const std::vector<std::shared_ptr<boost::property_tree::ptree>> getPacketsJson() noexcept;
	void clearReadyPackets() noexcept;


private:
	std::vector<std::shared_ptr<Packet>> readyPackets;
	std::unique_ptr<IncompletePacket> incompletePacket;

	std::pair<size_t, size_t> findLengthSignPos(std::string str);
	void addReadyPacket(std::string str) noexcept; // this function exists because a packet can have an invalid json
};

#endif // PACKETS_MANAGER_H
