#pragma once
#ifndef CUBOID_H
#define CUBOID_H

#include "Body.h"
class Cuboid :
	public Body
{
public:
	const int Cuboid_ID = this->Counter;
	Cuboid(Point3D refPoint, double xLength, double yLength, double zLength,Length::Unit unit=Length::METRE);
	~Cuboid();
	//returns the volume of the cuboid
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the cuboid
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the center of gravity
	Point3D getLocation() const;
	//returns the naming "cuboid"
	const char* getBodyName();
	//creates a cuboid trough the dialog
	static Body* createByDialog();
private:
	//the refPoint is in the lower front left corner
	Point3D refPoint;
	double xLength;
	double yLength;
	double zLength;
	
};

#endif // !CUBOID_H