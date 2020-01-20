#include "RoutingTable.h"
/*RoutingTableEntry& RountingTable::refSearch(ns3:: Ipv4Address ip)[
	auto itr = rTable.begin();
	while(itr != rTable.end()){
	}
}
*/
std::pair<ns3::Ptr<ns3::NetDevice>, ns3::Ipv4InterfaceAddress> RoutingTable::search(ns3::Ipv4Address ip){
	auto itr = rTable.begin();
	std::pair<ns3::Ptr<ns3::NetDevice>, ns3::Ipv4InterfaceAddress> retValue;
	retValue.first = 0;
	retValue.second = ns3::Ipv4InterfaceAddress();
	while(itr != rTable.end()){
		if(itr->getDsptIp() == ip){
			retValue.first = itr->getDevice();
			retValue.second = itr->getLink();
			return retValue;
		}
		else itr++;
	}
	return retValue;
}
void RoutingTable::addRouteEntry(RoutingTableEntry& rte){
	rTable.push_back(rte);
}
bool RoutingTable::deleteRouteEntry(ns3::Ipv4Address ip){
	auto itr = rTable.begin();
	while(itr != rTable.end()){
		if(itr->getDsptIp() == ip){
			rTable.erase(itr);
			return true;
		}
		else itr++;
	}
	return false;
}
bool RoutingTable::exist(ns3::Ipv4Address ip){
	auto itr = rTable.begin();
	while(itr != rTable.end()){
		if(itr->getDsptIp() == ip) return true;
		else itr++;
	}
	return false;
}

