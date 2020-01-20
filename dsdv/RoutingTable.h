#include "RoutingTableEntry.cc"
#include <vector>
#include <utility>
class RoutingTable{
	private:
		std::vector<RoutingTableEntry> rTable;
	public:
		std::pair<ns3::Ptr<ns3::NetDevice>,ns3::Ipv4InterfaceAddress> search(ns3::Ipv4Address ip);
		bool deleteRouteEntry(ns3::Ipv4Address ip);
		bool addRouteEntry(RoutingTableEntry& rte);
		bool lookUp(ns3::Ipv4Address);
};
		
