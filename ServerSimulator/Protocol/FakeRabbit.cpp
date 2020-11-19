#include "FakeRabbit.h"
#include <thread>

void FakeRabbit::ProcessQueue()
{
	if (rabbitQueue.empty())
	{
		return;
	}
	Task t = rabbitQueue.front();
	rabbitQueue.pop();
	std::thread taskThread([&t]()
		{
			t.doAThing();
			return true;
		});
}

void FakeRabbit::AddToQueue(Task task)
{
	rabbitQueue.push(task);
}