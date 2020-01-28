#include "RoutingProtocol.h"
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
           NS_LOG_LOGIC (mainAddress << " is forwarding packet " << p->GetUid ()
                                       << " to " << dst
                                       << " from " << header.GetSource ()
                                       << " via nexthop neighbor " << toDst.getNextHop ());
           ucb (route,p,header);
           return true;
         }
     } 
      else
      { //we will direct this packet for interzone processsing
      }
      

     
      
 }   