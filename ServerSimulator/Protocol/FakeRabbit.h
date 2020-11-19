#pragma once
#include <queue>
#include "../Server/Task.h"

class FakeRabbit
{
public:
	FakeRabbit()
	{

	}

	void ProcessQueue();
	void AddToQueue(Task task);

private:
	std::queue<Task> rabbitQueue;
};