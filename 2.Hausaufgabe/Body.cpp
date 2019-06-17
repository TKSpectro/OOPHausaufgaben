#include "Body.h"

int Body::Counter = 0;

Body::Body()
{
}

Body::~Body()
{
}

int Body::getCount() const
{
	return Counter;
}
