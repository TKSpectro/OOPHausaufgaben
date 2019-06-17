#pragma once
#ifndef CONE_H
#define CONE_H

#include "Body.h"
class Cone :
	public Body
{
public:
	const int Cone_ID = this->Counter;
	Cone(Point3D refPoint, double radius, double height, Length::Unit uni = Length::METRE);
	~Cone();
	//returns the volume of the cone
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the cone
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the center of gravity
	Point3D getLocation() const;
	//returns the naming "cone"
	const char* getBodyName();
	//creates a cone trough the dialog
	static Body* createByDialog();
private:
	//the refPoint is the center of the circle on the bottom of the cone
	Point3D refPoint;
	double radius;
	double height;

};

#endif // !CONE_H