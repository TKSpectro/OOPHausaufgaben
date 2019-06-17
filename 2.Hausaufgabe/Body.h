#pragma once
#ifndef BODY_H
#define BODY_H
#include <iostream>
#include "Length.h"
#include "Point3D.h"

using namespace std;

using namespace std;
class Body
{
	
public:
	Body();
	~Body();
	virtual double getVolume(Length::Unit unit = Length::METRE) const = 0;
	virtual double getSurface(Length::Unit unit = Length::METRE) const = 0;
	virtual const char* getBodyName() = 0;
	virtual Point3D getLocation() const = 0;
	int getCount() const;
protected:
	static int Counter ;

};

#endif // !BODY_H