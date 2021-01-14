#include "Client.h"
#include <iostream>
#include "../Protocol/Request.h"

using namespace std;

Packet Client::SerializeRequest(Request& r)
{
	uint8_t clientaddr = reinterpret_cast<uint8_t>(r.GetClient);
	Packet p(clientaddr, r.GetServerCommand());
	return p;
}

void Client::SendMessage()
{
	Request r(this, 1);
	Packet p = SerializeRequest(r);
	clientNetworkConnection.AddToRequestQueue(p);
}


void Client::ReceiveMessage(Response r)
{
	clientNetworkConnection.ProcessResponseQueue();
}




