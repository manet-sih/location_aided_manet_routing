#include <ns3/ipv4-address.h>
#include <ns3/ipv4-interface-container.h>
#include <ns3/net-device.h>
class RoutingTableEntry{
	private: 
		ns3::Ipv4Address dstIp;
		uint32_t seqNumber;
		uint32_t hopsCount;
		ns3::Ptr<ns3::NetDevice> device;
		ns3::Ipv4InterfaceAddress outputLinkInterface;
	public:
		RoutingTableEntry(ns3::Ipv4Address ip = ns3::Ipv4Address() ,uint32_t seq_num= 0,uint32_t hops_count = 0,ns3::Ptr<ns3::NetDevice> dev= 0, ns3::Ipv4InterfaceAddress outputLinkInterface = ns3::Ipv4InterfaceAddress());
		~RoutingTableEntry();
		RoutingTableEntry();
		uint32_t getSeqNumber() const;
		void setSeqNumber(uint32_t seq_number);
		uint32_t getHopsCount() const;
		void setHopsCount(uint32_t hops_count);
		ns3::Ipv4Address getDsptIp() const;
		ns3::Ptr<ns3::NetDevice> getDevice() const;
		void setDevice(ns3::Ptr<ns3::NetDevice> dev);
		ns3::Ipv4InterfaceAddress getLink() const;
		void setLink(ns3::Ipv4InterfaceAddress link);
};


