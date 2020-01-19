#include <map>
#include <ns3/ipv4-address.h>
#include "Location.h"
class PeripheralTable{
	std::map<ns3::Ipv4Address,Location> map;
	public:
	void addEntry(ns3::Ipv4Address,Location loc);
	void removeEntry(ns3::Ipv4Address addr);
	Location getLocation(ns3::Ipv4Address addr);
	bool exists(ns3::Ipv4Address addr);
	std::map<ns3::Ipv4Address,Location>::iterator getIterator();
};
