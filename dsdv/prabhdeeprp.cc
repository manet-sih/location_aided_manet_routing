#include "RoutingProtocol.h" 

ns3::Ptr<ns3::Socket> RoutingProtocol::findSocketWithInterfaceAddress(ns3::Ipv4InterfaceAddress interface) const{
	auto itr = socketToInterfaceMap.begin();
	while(itr != socketToInterfaceMap.end()){
		if(itr->second == interface) return itr->first;
	}
	return NULL;
}
