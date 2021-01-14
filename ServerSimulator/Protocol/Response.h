#pragma once
class Response
{
public:
	Response(Client* client, uint8_t command)
		:m_client(client)
		,m_command(command)
	{

	}
	Client* GetClient() { return m_client; }
	uint8_t GetCommand() { return m_command; }
private:
	Response();
	//0- fail, 2 = success
	Client* m_client;
	uint8_t m_command;
};

