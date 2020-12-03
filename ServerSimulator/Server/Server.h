#pragma once
#include "../Protocol/Network.h"

class Server
{
public:
	Server(Network& n)
		: serverNetworkConnection(n)
	{

	}
	void Tick();
private:
	Server();
	Network& serverNetworkConnection;
};

