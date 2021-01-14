#pragma once
#include <vector>
class Packet
{
public:
	Packet(uint8_t client, uint8_t data)
	{
		m_data.push_back(client);
		m_data.push_back(data);
	}

	uint8_t GetHeader() { return m_data[0]; };
	uint8_t GetData() { return m_data[1]; };
private:
	Packet(){}
	//0 - header
	//1+ - data
	std::vector<uint8_t> m_data;
};