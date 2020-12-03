#include "Client/Client.h"
#include "Server/Server.h"
#include <iostream>
#include <string>

int main()
{
	Network n;
	Client c1(n);
	Client c2(n);

	Server s(n);

	c1.SendMessage();
	c2.SendMessage();
	s.Tick();
	s.Tick();

	c1.ReceiveMessage();
	c2.ReceiveMessage();

	return 0;
}

