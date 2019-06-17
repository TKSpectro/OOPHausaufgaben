#pragma once
#ifndef HOUSE_H
#define HOUSE_H
#include "Body.h"
#include "Length.h"
class House :
	public Body
{
public:
	House(Point3D refPoint, double cWidth, double cDepth, double cHeight, double prismHeight, Length::Unit unit = Length::METRE);
	~House();
	//returns the volume of the house
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the house
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the center of gravity
	Point3D getLocation() const;
	//returns the naming "house"
	const char* getBodyName();
	//starts the creation of a house through console inputs
	static Body* createByDialog();
private:
	Point3D refPoint;
	//cuboid:
	double cWidth;
	double cDepth;
	double cHeight;
	//prism:
	double prismHeight;
};

#endif // !HOUSE_H