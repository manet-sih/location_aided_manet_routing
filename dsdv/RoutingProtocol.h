#include "dsdv-packet.h"
#include "RoutingTable.h"
#include "PeripheralTable.h"
#include <ns3/ipv4-routing-protocol.h>
class RoutingProtocol:public ns3::Ipv4RoutingProtocol{
	private:
		ns3::Ipv4Address nodeAddress;
		ns3::Ptr<ns3::Ipv4> ptrIp;
		RoutingTable routingTable;
		std::map<ns3::Ptr<ns3::Socket>,ns3::Ipv4InterfaceAddress> socketToInterfaceMap;
	private:
		void start(); //not implemented
		ns3::Ptr<ns3::Socket> findSocketWithInterfaceAddress(ns3::Ipv4InterfaceAddress ) const;	//implemented
		void recvDsdv(ns3::Ptr<ns3::Socket>); //not implemented
		void drop(ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header &, ns3::Socket::SocketErrno); //not implemented
		void send(ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header &); //not implemented
		void sendPeriodicUpdates();
	public:	
		static uint32_t zoneRadius;
		RoutingProtocol();//not implemented
		~RoutingProtocol();//not implemented
   		static ns3::TypeId GetTypeId (void);//extra

	
  		static const uint32_t DSDV_PORT;
		virtual void NotifyAddAddress(uint32_t interface,ns3::Ipv4InterfaceAddress); //implemented
		virtual void NotifyRemoveAddress(uint32_t interfaceNo, ns3::Ipv4InterfaceAddress);//implemented
		virtual void NotifyInterfaceUp(uint32_t );//implemented
		virtual void NotifyInterfaceDown(uint32_t );//implemented
		virtual void SetIpv4(ns3::Ptr<ns3::Ipv4>);//not implemented
  		bool RouteInput (ns3::Ptr<const ns3::Packet> p, const ns3::Ipv4Header &header, ns3::Ptr<const ns3::NetDevice> idev, UnicastForwardCallback ucb,MulticastForwardCallback mcb, LocalDeliverCallback lcb, ErrorCallback ecb);
		ns3::Ptr<ns3::Ipv4Route> LoopbackRoute (const ns3::Ipv4Header & header, ns3::Ptr<ns3::NetDevice> oif) const;
		ns3::Ptr<ns3::Ipv4Route> RouteOutput (ns3::Ptr<ns3::Packet> p, const ns3::Ipv4Header &header, ns3::Ptr<ns3::NetDevice> oif,ns3::Socket::SocketErrno &sockerr);
		void DoDispose();
};
