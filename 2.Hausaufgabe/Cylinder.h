#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H
#define _USE_MATH_DEFINES
#include<math.h>
#include "Body.h"
class Cylinder :
	public Body
{
public:
	const int Cylinder_ID = this->Counter;
	Cylinder(Point3D refPoint, double radius, double height,Length::Unit unit=Length::METRE);
	~Cylinder();
	//returns the volume of the cylinder....
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the cylinder
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the center of gravity
	Point3D getLocation() const;
	//returns the naming "cylinder"
	const char* getBodyName();
	//creates a cylinder trough the dialog
	static Body* createByDialog();
private:
	//the refPoint is the center of the circle on the bottom
	Point3D refPoint;
	double radius;
	double height;
};

#endif // !CYLINDER_H