#include "PeripheralTable.h"
void PeripheralTable::addEntry(ns3::Ipv4Address addr, Location loc){
	auto itr = map.find(addr);
	if(itr!=map.end()){
		itr->second = loc;
	}
	else{
		map[addr] = loc;
	}
}
void PeripheralTable::removeEntry(ns3::Ipv4Address addr){
	auto itr = map.find(addr);
	if(itr!=map.end()){
		map.erase(itr);
	}
}
Location PeripheralTable::getLocation(ns3::Ipv4Address addr){
	auto itr = map.find(addr);
	if(itr==map.end()) throw "NO SUCH NODE";
	return itr->second;
}
bool PeripheralTable::exists(ns3::Ipv4Address addr){
	return !(map.find(addr)==map.end());
}
std::map<ns3::Ipv4Address,Location>::iterator PeripheralTable::getIterator(){
	return map.begin();
}
