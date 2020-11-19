#include "../Protocol/FakeRabbit.h"

FakeRabbit requestQueue;
FakeRabbit responseQueue;

void addToRequestQueue(Task task)
{
	requestQueue.AddToQueue(task);
}

void addToResponseQueue(Task task)
{
	responseQueue.AddToQueue(task);
}

int main()
{

}

