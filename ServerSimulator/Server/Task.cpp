#include "Task.h"
#include <shared_mutex>

std::recursive_mutex taskMutex;

void Task::doAThing()
{
	std::unique_lock<std::recursive_mutex> lock(taskMutex);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}
