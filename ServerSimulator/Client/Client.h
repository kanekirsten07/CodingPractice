#pragma once
#include "../Protocol/Network.h"
class Client
{
public:
	Client(Network& n)
		: clientNetworkConnection(n)
	{

	}
	void SendMessage();
	void ReceiveMessage();
private:
	Client();
	Network& clientNetworkConnection;
};

