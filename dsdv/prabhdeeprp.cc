#include "RoutingProtocol.h" 
#include "ns3/uinteger.h"
#include "ns3/udp-socket-factory.h"
/*static ns3::TypeId GetTypeId ()
{
	static ns3::TypeId tid = ns3::TypeId ("ns3::dsdv::DeferredRouteOutputTag")
		.SetParent<ns3::Tag> ()
		.SetGroupName ("Dsdv")
		.AddConstructor<DeferredRouteOutputTag> ()
		;
	return tid;
}
*/
//******dsdv_port //EMPTY
ns3::Ptr<ns3::Socket> RoutingProtocol::findSocketWithInterfaceAddress(ns3::Ipv4InterfaceAddress interface) const{
	auto itr = socketToInterfaceMap.cbegin();
	while(itr != socketToInterfaceMap.cend()){
		if(itr->second == interface) return itr->first;
	}
	return NULL;
}
void RoutingProtocol::notifyInterfaceDown(uint32_t interface){
	ns3::Ptr<ns3::Socket> socket = findSocketWithInterfaceAddress(ptrIp->GetAddress(interface,0));
	socket->Close();
	socketToInterfaceMap.erase(socket);
	routingTable.deleteRoutesWithInterface(ptrIp->GetAddress(interface,0));
	//Message printing for interface up
}
void RoutingProtocol::notifyInterfaceUp(uint32_t interface){
	//Message printing for interface up
	ns3::Ipv4InterfaceAddress iface = ptrIp->GetAddress(interface,0);
	ns3::Ptr<ns3::Socket> socket = ns3::Socket::CreateSocket (GetObject<ns3::Node> (), ns3::UdpSocketFactory::GetTypeId ()); 
	socket->SetRecvCallback (MakeCallback (&RoutingProtocol::recvDsdv,this));
	socket->BindToNetDevice (ptrIp->GetNetDevice (interface));
	socket->Bind (ns3::InetSocketAddress (ns3::Ipv4Address::GetAny (), DSDV_PORT));
	socket->SetAllowBroadcast (true);
	socket->SetAttribute ("IpTtl",ns3::UintegerValue (1));
	socketToInterfaceMap.insert (std::make_pair (socket,iface));
	ns3::Ptr<ns3::NetDevice> dev = ptrIp->GetNetDevice (ptrIp->GetInterfaceForAddress (iface.GetLocal ()));
	/*inclomplete getlocal get net device"*/


}	
