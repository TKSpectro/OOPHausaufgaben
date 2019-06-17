#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Body.h"
class Sphere :
	public Body
{
public:
	const int Sphere_ID = this->Counter;
	Sphere(Point3D refPoint, double radius,Length::Unit unit=Length::METRE);
	~Sphere();
	//returns the volume of the sphere
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the sphere
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the center of gravity
	Point3D getLocation() const;
	//returns the naming "sphere"
	const char* getBodyName();
	//starts the creation of a sphere through console inputs
	static Body* createByDialog();
private:
	//the refPoint is the middle of the sphere
	Point3D refPoint;
	double radius;
};

#endif // !SPHERE_H