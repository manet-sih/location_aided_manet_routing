#include "RoutingTableEntry.h"
#include <vector>
#include <utility>
class RoutingTable{
	private:
		std::vector<RoutingTableEntry> rTable;
	public:
		RoutingTable();
		RoutingTableEntry& refSearch(ns3::Ipv4Address addr) ;
		//std::pair<ns3::Ptr<ns3::NetDevice>, ns3::Ipv4InterfaceAddress> search(ns3::Ipv4Address ip);
		bool deleteRouteEntry(ns3::Ipv4Address ip);
		void addRouteEntry(RoutingTableEntry& rte);
		bool exist(ns3::Ipv4Address ip) const;
			
};
		
