#include "PeripheralEntry.h"
PeripheralEntry::PeripheralEntry(ns3::Ipv4Address addr,Location loc) : addr{addr},loc{loc}{}
ns3::Ipv4Address PeripheralEntry::getAddress(){
	return addr;
}
Location PeripheralEntry::getLocation(){
	return loc;
}
void PeripheralEntry::setIP(ns3::Ipv4Address addr){
	this->addr = addr;
}
void PeripheralEntry::setLocation(Location loc){
	this->loc = loc;
}
