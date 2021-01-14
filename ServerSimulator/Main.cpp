#include "Client/Client.h"
#include "Server/Server.h"
#include <iostream>
#include <string>

int main()
{
	Network n;
	Client c1(n, 1);
	Client c2(n, 2);

	Server s(n);

	c1.SendMessage();
	c2.SendMessage();

	bool m_running = true;
	std::string command;

	while (m_running)
	{
		s.Run();
		std::cout << "Server Running. Enter 'shutdown' to shut server down." << std::endl;
		std::getline(std::cin, command);

		if (command.compare("shutdown") == 0)
		{
			s.Shutdown();
			m_running = false;
		}
	}
	
	return 0;
}

