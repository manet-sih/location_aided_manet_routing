#include <ns3/ipv4-address.h>
#include <ns3/ipv4-interface-container.h>
#include <ns3/net-device.h>
class RoutingTableEntry{
	private: 
		ns3::Ipv4Address dstIp;
		uint32_t seqNumber;
		uint32_t hopsCount;
		ns3::Ipv4InterfaceAddress outputLinkInterface;
		ns3::Ptr<ns3::NetDevice> device;
	public:
		RoutingTableEntry(ns3::Ipv4Address dstIp = ns3::Ipv4Address() ,uint32_t seqNumber = 0,uint32_t hopsCount = 0,ns3::Ptr<ns3::NetDevice> device = 0, ns3::Ipv4InterfaceAddress outputLinkInterface = ns3::Ipv4InterfaceAddress());
		~RoutingTableEntry();
		RoutingTableEntry();
		uint32_t getSeqNumber();
		void setSeqNumber(uint32_t seq_number);
		uint32_t getHopsCount();
		void setHopsCount(uint32_t hops_count);
		ns3::Ipv4Address getDsptIp();
};


