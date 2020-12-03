#include "Server.h"
#include <thread>

void::Server::Tick()
{
	Network& connection = serverNetworkConnection;
	std::thread taskThreadProcess([&connection]()
		{
			connection.ProcessRequestQueue();
			return true;
		});

	taskThreadProcess.join();

	std::thread taskThreadSendResponse([&connection]()
		{
			Packet p;
			connection.AddToResponseQueue(p);
			return true;
		});
	taskThreadSendResponse.join();
}