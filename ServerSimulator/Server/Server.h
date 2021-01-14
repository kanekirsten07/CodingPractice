#pragma once
#include "../Protocol/Network.h"
#include <functional>
#include <unordered_map>
#include "../Client/Client.h"
#include <thread>
#include "../Protocol/Request.h"
#include "../Protocol/Packet.h"

using ResponseCB = std::function<void(uint32_t retrunValue, const Response&)>;
using Handler = std::function<void(const Request&, ResponseCB)>;

class Server
{
public:
	Server(Network& n)
		: serverNetworkConnection(n)
	{

	}
	void Run();
	void Shutdown();
	void RegisterHandler(uint32_t packetId, Handler);
private:
	Server();
	Network& serverNetworkConnection;

	std::thread m_serverThread;
	bool m_shutdown = false;
	std::unordered_map<uint32_t, Handler> m_handlers;
	std::vector<Client> m_subscribers;

	Request DeserializeRequest(Packet& p);
	Packet SerializeResponse(Response& r);
};

