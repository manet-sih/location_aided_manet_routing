#include "RoutingTableEntry.h"

RoutingTableEntry::RoutingTableEntry(ns3::Ipv4Address destIp,uint32_t seqNumber,uint32_t hops,ns3::Ipv4InterfaceAddress interface,ns3::Ipv4Address nextHop,ns3::Time lifetime,ns3::Time settlingTime,bool changed,ns3::Ptr<ns3::NetDevice> dev):
	dstIp(destIp),
	seqNumber(seqNumber),
	hopsCount(hops),
	outputLinkInterface(interface),
	changed(changed),
	lifeTime(lifetime),
	settlingTime(settlingTime){
		route = ns3::Create<ns3::Ipv4Route>();
		route->SetGateway(nextHop);
		route->SetDestination(dstIp);
		route->SetSource(outputLinkInterface.GetLocal());
		route->SetOutputDevice(dev);
	}
RoutingTableEntry::RoutingTableEntry(){
}	
inline uint32_t RoutingTableEntry:: getSeqNumber() const{
	return this->seqNumber;
}
inline uint32_t RoutingTableEntry::getHopsCount() const{
	return this->hopsCount;
}
inline ns3::Ptr<ns3::NetDevice> RoutingTableEntry::getDevice() const{
	return route->GetOutputDevice();
}
inline ns3::Ipv4InterfaceAddress RoutingTableEntry::getLink() const{
	return outputLinkInterface;
}
inline ns3::Ipv4Address RoutingTableEntry::getDsptIp() const{
	return this->dstIp;
}
inline ns3::Ptr<ns3::Ipv4Route> RoutingTableEntry::getRoute() const{
	return route;
}
inline bool RoutingTableEntry::isChanged() const{
	return changed;
}
inline ns3::Time RoutingTableEntry::getLifeTime() const{
	return ns3::Simulator::Now() - lifeTime;
}
inline ns3::Time RoutingTableEntry::getSettlingTime() const{
	return settlingTime;
}
inline ns3::Ipv4Address RoutingTableEntry::getNextHop() const{
	return route->GetGateway();
}
void RoutingTableEntry:: setSeqNumber(uint32_t seq_number){
	this->seqNumber = seq_number;
}
void RoutingTableEntry::setHopsCount(uint32_t hops_count){
	this->hopsCount = hops_count;
}
void RoutingTableEntry::setDevice(ns3::Ptr<ns3::NetDevice> dev){
	route->SetOutputDevice(dev);
}
void RoutingTableEntry::setLink(ns3::Ipv4InterfaceAddress link){
	outputLinkInterface = link;
}
inline void RoutingTableEntry::setChanged(bool flag){
	changed = flag;
}
inline void RoutingTableEntry::setLifeTime(ns3::Time time){
	lifeTime = time;
}
inline void RoutingTableEntry::setSettlingTime(ns3::Time time){
	settlingTime = time;
}
inline void RoutingTableEntry::setNextHop(ns3::Ipv4Address hop){
	route->SetGateway(hop);
}
inline void RoutingTableEntry::setRoute(ns3::Ptr<ns3::Ipv4Route> route){
	this->route = route;
}
