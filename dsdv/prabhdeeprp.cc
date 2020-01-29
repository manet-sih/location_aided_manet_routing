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
void RoutingProtocol::NotifyInterfaceDown(uint32_t interface){
	ns3::Ptr<ns3::Socket> socket = findSocketWithInterfaceAddress(ptrIp->GetAddress(interface,0));
	socket->Close();
	socketToInterfaceMap.erase(socket);
	routingTable.deleteRoutesWithInterface(ptrIp->GetAddress(interface,0));
	//Message printing for interface up
}
void RoutingProtocol::NotifyInterfaceUp(uint32_t interface){
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
void RoutingProtocol::NotifyAddAddress(uint32_t interfaceNo,ns3::Ipv4InterfaceAddress address){
	if (!ptrIp->IsUp (interfaceNo))
	{
		return;
	}
	ns3::Ipv4InterfaceAddress iface = ptrIp->GetAddress (interfaceNo,0);
	ns3::Ptr<ns3::Socket> socket = RoutingProtocol::findSocketWithInterfaceAddress (iface);
	if (!socket)
	{
		if (iface.GetLocal () == ns3::Ipv4Address ("127.0.0.1"))
		{
			return;
		}
		ns3::Ptr<ns3::Socket> socket = ns3::Socket::CreateSocket (GetObject<ns3::Node> (),ns3::UdpSocketFactory::GetTypeId ());
		/*imortant 		//socket->SetRecvCallback (MakeCallback (&RoutingProtocol::RecvDsdv,this));     */
		socket->BindToNetDevice (ptrIp->GetNetDevice (interfaceNo));
		socket->Bind (ns3::InetSocketAddress (ns3::Ipv4Address::GetAny (), DSDV_PORT));
		socket->SetAllowBroadcast (true);
		socketToInterfaceMap.insert (std::make_pair (socket,iface));
		ns3::Ptr<ns3::NetDevice> dev = ptrIp->GetNetDevice (ptrIp->GetInterfaceForAddress (iface.GetLocal ()));
		//important		RoutingTableEntry rt (/*device=*/ dev, /*dst=*/ iface.GetBroadcast (),/*seqno=*/ 0, /*iface=*/ iface,/*hops=*/ 0,
		//				/*next hop=*/ iface.GetBroadcast (), /*lifetime=*/ ns3::Simulator::GetMaximumSimulationTime ());   
		routingTable.addRouteEntry (rt);
	}
}
void RoutingProtocol::NotifyRemoveAddress(uint32_t interfaceNo, ns3::Ipv4InterfaceAddress ifaceAddress){
	ns3::Ptr<ns3::Socket> socket = findSocketWithInterfaceAddress(ifaceAddress);
	if(socket != NULL){
		socketToInterfaceMap.erase (socket);
		if (ptrIp->GetNAddresses (interfaceNo)){	
			ns3::Ipv4InterfaceAddress iface = ptrIp->GetAddress(interfaceNo,0);
			ns3::Ptr<ns3::Socket> socket = ns3::Socket::CreateSocket (GetObject<ns3::Node> (),ns3::UdpSocketFactory::GetTypeId ());
			socket->SetRecvCallback (MakeCallback (&RoutingProtocol::recvDsdv,this));
			socket->Bind (ns3::InetSocketAddress (ns3::Ipv4Address::GetAny (), DSDV_PORT));
			socket->SetAllowBroadcast (true);
			socketToInterfaceMap.insert (std::make_pair (socket,iface));
		}
	}
}

bool RoutingProtocol::RouteInput (ns3::Ptr<const ns3:: Packet> p, const ns3::Ipv4Header &header, ns3::Ptr<const ns3::NetDevice> idev, UnicastForwardCallback ucb, MulticastForwardCallback mcb, LocalDeliverCallback lcb, ErrorCallback ecb){
	if(socketToInterfaceMap.empty())  return false;
	ns3::Ipv4Address src=header.GetSource();
	ns3::Ipv4Address dst=header.GetDestination();
	for(auto itr =socketToInterfaceMap.begin();itr!=socketToInterfaceMap.end();itr++)
	{
		if( src == (itr->second).GetLocal())
			return true;
	}
	RoutingTableEntry rte;
	for(auto itr = socketToInterfaceMap.begin();itr != socketToInterfaceMap.end();itr++){
		ns3::Ipv4InterfaceAddress ifaceAddr = itr->second;
		if(ptrIp->GetInterfaceForAddress(ifaceAddr.GetLocal()) == ptrIp->GetInterfaceForDevice(idev)){
			if(dst == ifaceAddr.GetBroadcast() || dst.IsBroadcast()){
				ns3::Ptr<ns3::Packet> packet =  p->Copy();
				if(lcb.IsNull() == false){
					lcb(p,header,ptrIp->GetInterfaceForDevice(idev));
				}
				else{
					ecb(p,header,ns3::Socket::ERROR_NOROUTETOHOST);
				}
				if(header.GetTtl() > 1){
					RoutingTableEntry toBroadcast;
					if(routingTable.search(dst,toBroadcast)){
							ns3::Ptr<ns3::Ipv4Route> route = toBroadcast.GetRoute();
							ucb(route,packet,header);
					}
					else{
							//drop packet
					}
				}
				return true;
			}
		}
	}

							RoutingTableEntry toDst;
							if (routingTable.search(dst,toDst))
							{
							RoutingTableEntry ne;
							if (routingTable.search(toDst.getNextHop(),ne))
							{
								ns3::Ptr<ns3::Ipv4Route> route = ne.getRoute ();
							}
							}
else{ 
	//we will direct this packet for interzone processsing
}   
}
void RoutingProtocol::DoDispose(){
	for(auto itr = socketToInterfaceMap.cbegin();itr != socketToInterfaceMap.cend();itr++){
			(itr->first)->Close();
	}
	socketToInterfaceMap.clear();
	ns3::Ipv4RoutingProtocol::DoDispose();
}

