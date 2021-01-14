#pragma once
#include <queue>
#include "Packet.h"


class Network
{
public:
	Packet& ProcessRequestQueue();
	Packet& ProcessResponseQueue();
	void AddToRequestQueue(Packet packet);
	void AddToResponseQueue(Packet packet);

private:
	std::queue<Packet> requestQueue;
	std::queue<Packet> responseQueue;
};