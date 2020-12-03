#include "Client.h"
#include <iostream>

using namespace std;


void Client::SendMessage()
{
	Packet p;
	clientNetworkConnection.AddToRequestQueue(p);
}

void Client::ReceiveMessage()
{
	clientNetworkConnection.ProcessResponseQueue();
}




