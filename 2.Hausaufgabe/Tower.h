#pragma once
#ifndef TOWER_H
#define TOWER_H
#include "Cone.h"
#include "Cylinder.h"
#include "Body.h"
#include "Length.h"
class Tower :
	public Body
{
public:
	Tower(Point3D refPoint, double radius, double coneHeight, double cylinderHeight, Length::Unit uni = Length::METRE);
	~Tower();
	//returns the volume of the tower
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the tower
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the location (reference point)
	Point3D getLocation() const;
	//returns the naming "tower"
	const char* getBodyName();
	//starts the creation of a tower through console inputs
	static Body* createByDialog();
private:
	//the refPoint is the center of the circle on the bottom of the tower
	Point3D refPoint;
	double radius;
	double coneHeight;
	double cylinderHeight;
};

#endif // !TOWER_H