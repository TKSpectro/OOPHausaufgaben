#pragma once
#ifndef BODYQUEUE_H
#define BODYQUEUE_H
#include <queue>
#include <list>
#include "Body.h"

class BodyQueue
{
public:
	BodyQueue();
	~BodyQueue();

	void enqueue(const Body& body);
	const Body* dequeue();
	bool isEmpty();
private:
	std::queue<Body*, std::list<Body*>> queue;
};
#endif // !BODYQUEUE_H