#pragma once
#include "../Protocol/Network.h"
class Client
{
public:
	Client(Network& n, uint8_t clientId)
		: clientNetworkConnection(n)
		,m_clientID(clientId)
	{

	}
	void SendMessage();
	void ReceiveMessage();
private:
	Client();
	Packet SerializeRequest(Request& r);
	Network& clientNetworkConnection;
	uint8_t m_clientID;
};

