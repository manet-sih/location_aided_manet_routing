#include <ns3/ipv4-address.h>
#include <ns3/ipv4-interface-container.h>
#include <ns3/nstime.h>
#include <ns3/net-device.h>
#include <ns3/ipv4-route.h>
class RoutingTableEntry{
	private: 
		ns3::Ipv4Address dstIp;
		uint32_t seqNumber;
		uint32_t hopsCount;
		ns3::Ipv4InterfaceAddress outputLinkInterface;
		ns3::Ptr<ns3::Ipv4Route> route;
		bool changed;
		ns3::Time lifeTime;
		ns3::Time settlingTime;
	public:
		RoutingTableEntry(ns3::Ipv4Address ip = ns3::Ipv4Address() ,uint32_t seq_num= 0,uint32_t hops_count = 0,ns3::Ptr<ns3::NetDevice> dev= 0, ns3::Ipv4InterfaceAddress outputLinkInterface = ns3::Ipv4InterfaceAddress());
		~RoutingTableEntry();
		RoutingTableEntry();
		inline uint32_t getSeqNumber() const;
		inline void setSeqNumber(uint32_t seq_number);
		inline uint32_t getHopsCount() const;
		inline void setHopsCount(uint32_t hops_count);
		inline ns3::Ipv4Address getDsptIp() const;
		inline ns3::Ptr<ns3::NetDevice> getDevice() const;
		inline void setDevice(ns3::Ptr<ns3::NetDevice> dev);
		inline ns3::Ipv4InterfaceAddress getLink() const;
		inline void setLink(ns3::Ipv4InterfaceAddress link);
		inline bool isChanged();
		inline void setChanged(bool flag);
		inline ns3::Time getLifeTime();
		inline void setLifeTime(ns3::Time time);
		inline ns3::Time getSettlingTime();
		inline void setSettlingTime(ns3::Time time);
		bool operator==(const RoutingTableEntry& entry){
			return dstIp == entry.dstIp;
		}
		inline void setNextHop(ns3::Ipv4Address hop);
		inline ns3::Ipv4Address getNextHop();
		inline void setRoute(ns3::Ptr<ns3::Ipv4Route> route);
		inline ns3::Ptr<ns3::Ipv4Route> getRoute();

};


