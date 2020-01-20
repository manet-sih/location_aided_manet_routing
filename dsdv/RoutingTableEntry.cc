#include "RoutingTableEntry.h"

RoutingTableEntry::RoutingTableEntry(ns3::Ipv4Address ip,uint32_t seq_num,uint32_t hops_count,ns3::Ptr<ns3::NetDevice> dev, ns3::Ipv4InterfaceAddress output_link_interface):dstIp(ip),seqNumber(seq_num),hopsCount(hops_count),device(dev),outputLinkInterface(output_link_interface){}

RoutingTableEntry::~RoutingTableEntry(){
}
RoutingTableEntry::RoutingTableEntry(){
}	
uint32_t RoutingTableEntry:: getSeqNumber(){
	return this->seqNumber;
}
void RoutingTableEntry:: setSeqNumber(uint32_t seq_number){
	this->seqNumber = seq_number;
}
uint32_t RoutingTableEntry::getHopsCount(){
	return this->hopsCount;
}
void RoutingTableEntry::setHopsCount(uint32_t hops_count){
	this->hopsCount = hops_count;
}
ns3::Ipv4Address RoutingTableEntry::getDsptIp(){
	return this->dstIp;
}
ns3::Ptr<ns3::NetDevice> RoutingTableEntry::getDevice(){
	return device;
}
void RoutingTableEntry::setDevice(ns3::Ptr<ns3::NetDevice> dev){
	device = dev;
}
ns3::Ipv4InterfaceAddress RoutingTableEntry::getLink(){
	return outputLinkInterface;
}
void RoutingTableEntry::setLink(ns3::Ipv4InterfaceAddress link){
	outputLinkInterface = link;
}
