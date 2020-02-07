#include "ns3/ipv4-l3-protocol.h"
#include "RoutingProtocol.h"
#include "ns3/packet.h"
bool RoutingProtocol::RouteInput (ns3::Ptr<const ns3:: Packet> p,
                              const ns3::Ipv4Header &header,
                              ns3::Ptr<const ns3::NetDevice> idev,
                              UnicastForwardCallback ucb,
                              MulticastForwardCallback mcb,
                              LocalDeliverCallback lcb,
                              ErrorCallback ecb)
 {
      if(socketToInterfaceMap.empty())  return false;
      ns3::Ipv4Address src=header.GetSource();
      ns3::Ipv4Address dst=header.GetDestination();
      for(auto itr =socketToInterfaceMap.begin();itr!=socketToInterfaceMap.end();itr++)
      {
          if( src == (itr->second).GetLocal())
            return true;
      }
      
      RoutingTableEntry rte;
      
     
         RoutingTableEntry toDst;
   if (routingTable.search(dst,toDst))
     {
       RoutingTableEntry ne;
       if (routingTable.search(toDst.getNextHop(),ne))
         {
           ns3::Ptr<ns3::Ipv4Route> route = ne.getRoute ();
       
           ucb (route,p,header);
           return true;
         }
          else
      { //we will direct this packet for interzone processsing
      }
      
     } 
     

     
      
}
ns3::Ptr<ns3::Ipv4Route> RoutingProtocol::RouteOutput (ns3::Ptr<ns3::Packet> p, const ns3::Ipv4Header &header, ns3::Ptr<ns3::NetDevice> oif,ns3::Socket::SocketErrno &sockerr)
{
   if (!p)
     {
       return RoutingProtocol::LoopbackRoute(header,oif);
     }
     if (socketToInterfaceMap.empty ())
     {
       
       ns3::Ptr<ns3::Ipv4Route> route;
       return route;
     }
      RoutingTableEntry rt;
      ns3::Ipv4Address dst = header.GetDestination ();
      if( routingTable.search(header.GetDestination (),rt))
      {
         ns3::Ptr<ns3::Ipv4Route> route=rt.getRoute();
          if(rt.getHopsCount()==1)
            {
               
              if (oif != 0 && route->GetOutputDevice () != oif)
                  return ns3::Ptr<ns3::Ipv4Route>();
            }
            return route;
      }
      else{
             RoutingTableEntry rti;
            if(routingTable.search(rt.getNextHop(),rti))
            {
               ns3::Ptr<ns3::Ipv4Route> route=rti.getRoute();
               if (oif != 0 && route->GetOutputDevice () != oif)
               {
                 return ns3::Ptr<ns3::Ipv4Route>();
               }
               return route;
            }
             
             
            
      }
     return LoopbackRoute (header,oif);

}
void RoutingProtocol::send(ns3::Ptr<ns3::Ipv4Route>route, ns3::Ptr<const ns3::Packet>packet, const ns3::Ipv4Header &header)
{
    ns3::Ptr<ns3::Ipv4L3Protocol> l3 =RoutingProtocol::ptrIp->GetObject<ns3::Ipv4L3Protocol> ();
   NS_ASSERT (l3 != 0);
   ns3::Ptr<ns3::Packet> p = packet->Copy ();
   l3->Send (p,route->GetSource (),header.GetDestination (),header.GetProtocol (),route);
}
void RoutingProtocol::sendPeriodicUpdates()
 {
    std::map<ns3::Ipv4Address, RoutingTableEntry>allroute;
    routingTable.getAllRoutes(allroute);
    if(allroute.empty())
    {
      return;
    }
     for (std::map<ns3::Ptr<ns3::Socket>, ns3::Ipv4InterfaceAddress>::const_iterator j = socketToInterfaceMap.begin (); j
        != socketToInterfaceMap.end (); ++j)
     { ns3::Ptr<ns3::Socket> socket = j->first;
       ns3::Ipv4InterfaceAddress iface = j->second;
       ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet> ();
       DsdvHeader dsdvHeader;
          for(auto itr=allroute.begin();itr!=allroute.end();itr++)
          {
            
           if (itr->second.getHopsCount() == 0)
             {
               RoutingTableEntry ownEntry;
               dsdvHeader.set_IP (ptrIp->GetAddress (1,0).GetLocal ());
               dsdvHeader.set_seq( itr->second.getSeqNumber() + 1);
               dsdvHeader.set_hops (itr->second.getHopsCount ()+1);
               dsdvHeader.set_loca(Location(0.0,0.0));
               routingTable.search(ptrIp->GetAddress (1,0).GetBroadcast (),ownEntry);

               ownEntry.setSeqNumber(dsdvHeader.get_seq());
              routingTable.updateRoute(ownEntry);
                packet->AddHeader(dsdvHeader);

             } 
             else{
                    dsdvHeader. set_IP (itr->second.getDsptIp());
               dsdvHeader.set_seq(itr->second.getSeqNumber());
               dsdvHeader.set_hops(itr->second. getHopsCount () + 1);
                dsdvHeader.set_loca(Location(0.0,0.0));
               packet->AddHeader (dsdvHeader);
             }
          } 
          if(dsdvHeader.get_hops()<=RoutingProtocol::zoneRadius)
             {
           socket->Send (packet);
       
       ns3::Ipv4Address destination;
       if (iface.GetMask () == ns3::Ipv4Mask::GetOnes ())
         {
           destination = ns3::Ipv4Address ("255.255.255.255");
         }
       else
         {
           destination = iface.GetBroadcast ();
         }
       socket->SendTo (packet, 0, ns3::InetSocketAddress (destination, DSDV_PORT)); 
             }
        
     }        
 }
