#pragma once
#include "../Client/Client.h"
class Request
{
public:
	Request(Client* c, uint8_t command)
		:m_client(c)
		,m_servercommand(command)
	{

	}

	Client* GetClient() { return m_client; }
	uint8_t GetServerCommand() { return m_servercommand; }
private:
	Request();
	Client* m_client;
	//0 - fail, 1 = success
	uint8_t m_servercommand;
};

