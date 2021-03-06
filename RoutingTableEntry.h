#include <ns3/ipv4-address.h>
#include <ns3/ipv4-interface-container.h>
#include <ns3/nstime.h>
#include <ns3/net-device.h>
#include <ns3/ipv4-route.h>
#include <ns3/simulator.h>
enum class EntryState{
	VALID,INVALID
};
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
		EntryState state;
	public:
		RoutingTableEntry(ns3::Ipv4Address destIp,uint32_t seqNumber,uint32_t hops,ns3::Ipv4InterfaceAddress interface,ns3::Ipv4Address nextHop,ns3::Time lifetime,ns3::Time settlingTime,bool changed,ns3::Ptr<ns3::NetDevice> dev);
		~RoutingTableEntry();
		RoutingTableEntry();
		inline uint32_t getSeqNumber() const;
		inline uint32_t getHopsCount() const;
		inline EntryState getEntryState() const;
		inline ns3::Ptr<ns3::NetDevice> getDevice() const;
		inline ns3::Ipv4Address getDsptIp() const;
		inline ns3::Ipv4InterfaceAddress getLink() const;
		inline ns3::Ptr<ns3::Ipv4Route> getRoute() const;
		inline bool isChanged() const;
		inline ns3::Time getLifeTime() const;
		inline ns3::Time getSettlingTime() const;
		inline ns3::Ipv4Address getNextHop() const;
		inline void setSeqNumber(uint32_t seq_number);
		inline void setHopsCount(uint32_t hops_count);
		inline void setDevice(ns3::Ptr<ns3::NetDevice> dev);
		inline void setLink(ns3::Ipv4InterfaceAddress link);
		inline void setChanged(bool flag);
		inline void setEntryState(EntryState state);
		inline void setLifeTime(ns3::Time time);
		inline void setSettlingTime(ns3::Time time);
		bool operator==(const RoutingTableEntry& entry){
			return dstIp == entry.dstIp;
		}
		inline void setNextHop(ns3::Ipv4Address hop) ;
		inline void setRoute(ns3::Ptr<ns3::Ipv4Route> route);

};


