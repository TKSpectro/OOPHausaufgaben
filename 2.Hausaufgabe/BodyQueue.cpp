#include "BodyQueue.h"

BodyQueue::BodyQueue()
{
}


BodyQueue::~BodyQueue()
{
}

void BodyQueue::enqueue(const Body& body)
{
	this->queue.push((Body*)(&body));
}

const Body* BodyQueue::dequeue()
{
	if(!this->queue.empty())
	{
		Body* body = this->queue.front();
		this->queue.pop();
		return body;
	}
	else
	{
		return nullptr;
	}
}

bool BodyQueue::isEmpty()
{
	return queue.empty();
}

