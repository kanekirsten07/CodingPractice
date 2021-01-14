#include "Server.h"
#include "../Protocol/Response.h"
#include "../Protocol/Request.h"
#include <thread>

Request Server::DeserializeRequest(Packet& p)
{
	uint8_t clientaddr = p.GetHeader();
	Client* c = reinterpret_cast<Client*>(clientaddr);
	uint8_t data = p.GetData();
	Request r (c, data);
	return r;
}

Packet Server::SerializeResponse(Response& r)
{
	uint8_t clientaddr = reinterpret_cast<uint8_t>(r.GetClient());
	Packet p(clientaddr, r.GetCommand());
	return p;
}

void Server::Run()
{
	Network& connection = serverNetworkConnection;
	m_serverThread = std::thread(
		[&connection, this]()
		{
			while (!m_shutdown)
			{
				Packet t = connection.ProcessRequestQueue();
				// 0. Deserializes
				// 1. find handler using information in packet header
				// 2. call handler with packet body
				//
				Request request = DeserializeRequest(t);
				/* Handler([&request, this](uint32_t retrunValue, const Response& response)
				 {
					//Serialize header in packet;
					uint8_t returnValue = 1;
					if (request.GetServerCommand() == 1)
					{
						 Response r (request.GetClient(), 2);	
						 Packet p = SerializeResponse(r);
						 connection.AddToResponseQueue(p);
					}

				 });
				*/
			}

			return true;
		});

}

void Server::Shutdown()
{
	m_shutdown = true;
	//wait for main thread to exit
	m_serverThread.join();
}


