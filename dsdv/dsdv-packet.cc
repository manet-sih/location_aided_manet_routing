#include "dsdv-packet.h"
DsdvHeader::DsdvHeader(){}
DsdvHeader::DsdvHeader(ns3::Ipv4Address a_d,uint32_t seq,uint32_t hop,Location loc)
{
	addr_dest=a_d; 
	seq_no_dest=seq;
	no_of_hops=hop;
	this->loc = loc;
}
ns3::TypeId DsdvHeader::GetTypeId (void)
{
	static ns3::TypeId tid = ns3::TypeId ("ns3::dsdv::DsdvHeader")
		.SetParent<ns3::Header> ()
		.SetGroupName ("Dsdv")
		.AddConstructor<DsdvHeader> ();
	return tid;
}
ns3::TypeId DsdvHeader::GetInstanceTypeId () const
{
	return GetTypeId ();
}
uint32_t DsdvHeader::GetSerializedSize () const
{
	return 32;
}
void DsdvHeader::Serialize (ns3::Buffer::Iterator i) const
{
	WriteTo (i, addr_dest);
	i.WriteHtonU32 (0);
	i.WriteHtonU32 (seq_no_dest);
	i.WriteHtonU32 (no_of_hops);
	i.WriteHtolsbU64((uint64_t)loc.getX());
	i.WriteHtonU64 ((float)this->loc.getY());
}

uint32_t DsdvHeader::Deserialize (ns3::Buffer::Iterator start)
{
	ns3::Buffer::Iterator i = start;
	ReadFrom (i, addr_dest);
	i.ReadU32();
	seq_no_dest= i.ReadNtohU32 ();
	no_of_hops= i.ReadNtohU32 ();
	loc.setX(i.ReadNtohU32 ());
	loc.setY(i.ReadNtohU32 ());
	uint32_t dist = i.GetDistanceFrom (start);
	NS_ASSERT (dist == GetSerializedSize ());
	return dist;
}

void DsdvHeader::Print (std::ostream &os) const
{
	os << "DestinationIpv4: " << addr_dest
		<< " Hopcount: " << no_of_hops 
		<< " SequenceNumber: " << no_of_hops<<"location"<<loc.getX()<<" "<<loc.getY();
}

void DsdvHeader::set_IP(ns3::Ipv4Address a_d){this->addr_dest=a_d;}
void DsdvHeader::set_seq( uint32_t seq){this->seq_no_dest=seq;}
void DsdvHeader::set_hops(uint32_t hop){ this->no_of_hops=hop;}
void DsdvHeader::set_loca(Location lo){loc =lo;}
ns3::Ipv4Address DsdvHeader::get_IP(){return addr_dest;}
uint32_t DsdvHeader::get_seq(){return  seq_no_dest; }
uint32_t DsdvHeader::get_hops(){return no_of_hops;}
Location DsdvHeader::get_loca(){ return loc;}
