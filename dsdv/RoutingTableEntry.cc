#include <RoutingTableEntry.h>

class RoutingTableEntry{
	Public:
		
		RoutingTableEntry(ns3::Ipv4Address destinationIp = ns3::Ipv4Address() ,
				uint32_t seq_number = 0,
				uint32_t hops_count = 0,
				ns3::Ptr<ns3::NetDevice> dev = 0, ns3::Ipv4InterfaceAddress output_link_interface= ns3::Ipv4InterfaceAddress()){
			dstIp = destinationIp;
			seqNumber = seq_number;
			hopsCount = hops_count;
			device = dev;
			outputLinkInterface = output_link_interface;}
		~RoutingTableEntry(){
		}
		RoutingTableEntry{
		}	
		uint32_t getSeqNumber(){
			return this->seqNumber;
		}
		void setSeqNumber(uint32_t seq_number){
			this->seqNumber = seq_number;
		}
		uint32_t getHopsCount(){
			return this->hopsCount;
		}
		void setHopsCount(uint32_t hops_count){
			this->hopsCount = hops_count;
		}
		ns3::Ipv4Address getDsptIp(){
			return this->dstIp;
		}
};


