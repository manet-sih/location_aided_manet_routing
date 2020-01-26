#include "dsdv-packet.h"
#include "RoutingTable.h"
#include "PeripheralTable.h"
#include <ns3/ipv4-routing-protocol.h>
class RoutingProtocol:public ns3::Ipv4RoutingProtocol{
	private:
		RoutingTable routingTable;
		std::map<ns3::Ptr<ns3::Socket>,ns3::Ipv4InterfaceAddress> socketToInterfaceMap;
	private:
		void start();
		ns3::Ptr<ns3::Socket> findSocketWithInterfaceAddress(ns3::Ipv4InterfaceAddress interface) const;			
		void recvDsdv(ns3::Ptr<ns3::Socket>);
		void drop(ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header &, ns3::Socket::SocketErrno);
		void send(ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header &);

	public:
		virtual void notifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress) const;
		virtual void notifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) const;
		virtual void interfaceup(uint32_t inteface) ;
		virtual void interfacedown(uint32_t interface);
		virtual void setIpv4(ns3::Ptr<ns3::Ipv4> ip);

};
