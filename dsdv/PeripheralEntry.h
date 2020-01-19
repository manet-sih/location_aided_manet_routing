#include "Location.h"
#include "ns3/ipv4-address.h"
class PeripheralEntry{
	ns3::Ipv4Address addr;
	Location loc;
	public:
	PeripheralEntry(ns3::Ipv4Address addr, Location loc);
	void setLocation(Location loc);
	void setIP(ns3::Ipv4Address addr);
	ns3::Ipv4Address getAddress();
	Location getLocation();
};
