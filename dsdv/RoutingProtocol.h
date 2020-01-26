#include "dsdv-packet.h"
#include "RoutingTable.h"
#include "PeripheralTable.h"
class RoutingProtocol{
	private:
		RoutingTable rTable;
		std::map<ns3::Ptr<ns3::Socket>,ns3::Ipv4InterfaceAddress> socketToInterfaceMap;
	private:
		void start();
		ns3::Ptr<ns3::Socket> findSocketWithInterfaceAddress(ns3::Ipv4InterfaceAddress interface) const;			
		void recvDsdv(ns3::Ptr<ns3::Socket>);
		void drop(ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header &, ns3::Socket::SocketErrno);
		void send(ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header &);

	public:
		void notifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress) const;
		void notifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) const;
		void ifaceup(uint32_t inteface) ;
		void ifacedown(uint32_t interface);
		void setIpv4(ns3::Ptr<ns3::Ipv4> ip);

};
