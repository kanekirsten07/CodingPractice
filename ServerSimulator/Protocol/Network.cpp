#include "Network.h"
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

std::recursive_mutex requestMutex;
std::recursive_mutex responseMutex;
Packet& Network::ProcessRequestQueue()
{
	std::unique_lock<std::recursive_mutex> lock(requestMutex);
	if (requestQueue.empty())
	{
		std::cout << "Request Queue is empty" << endl;
		return;
	}
	Packet& t = requestQueue.front();
	requestQueue.pop();
	std::cout << "Processing request packet!" << endl;
	return t;
} 

Packet& Network::ProcessResponseQueue()
{
	std::unique_lock<std::recursive_mutex> lock(responseMutex); 
	if(responseQueue.empty())
	{
		std::cout << "Response Queue is empty" << endl;
		return;
	}
	Packet& t = responseQueue.front();
	responseQueue.pop();
	std::cout << "Processing response packet!" << endl;

	return t;
}

void Network::AddToRequestQueue(Packet packet)
{
	std::unique_lock<std::recursive_mutex> lock(requestMutex);
	requestQueue.push(packet);
}


void Network::AddToResponseQueue(Packet packet)
{
	std::unique_lock<std::recursive_mutex> lock(responseMutex);
	responseQueue.push(packet);
}