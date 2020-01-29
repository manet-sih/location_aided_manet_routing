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
  
