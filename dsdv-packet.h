#include <iostream>
#include "ns3/header.h"
#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"
#include "Location.h"
#include "ns3/object-base.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"

class DsdvHeader
{
	NS_OBJECT_ENSURE_REGISTERED(DsdvHeader);

	private:
	ns3::Ipv4Address addr_dest;
	uint32_t seq_no_dest;
	uint32_t no_of_hops;
	Location loc;
	static ns3::TypeId GetTypeId(void);
	virtual ns3::TypeId GetInstanceTypeId(void) const;
	virtual uint32_t GetSerializedSize() const;
	virtual void Serialize(ns3::Buffer::Iterator start) const;
	virtual uint32_t Deserialize(ns3::Buffer::Iterator start);
	virtual void Print(std::ostream &os) const;

	public:
	DsdvHeader();
	DsdvHeader(ns3::Ipv4Address a_d, uint32_t seq, uint32_t hop, Location loc);
	void set_IP(ns3::Ipv4Address a_d);
	void set_seq(uint32_t seq);
	void set_hops(uint32_t hop);
	void set_loca(Location lo);
	ns3::Ipv4Address get_IP();
	uint32_t get_seq();
	uint32_t get_hops();
	Location get_loca();
};
