#pragma once
#ifndef PRISM_H
#define PRISM_H

#include "Body.h"
class Prism :
	public Body
{
public:
	const int Prism_ID = this->Counter;
	Prism(Point3D refPoint, double width, double height, double depth, Length::Unit unit = Length::METRE);
	~Prism();
	//returns the volume of the prism
	double getVolume(Length::Unit unit = Length::METRE) const;
	//returns the surface of the prism
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns center of gravity
	Point3D getLocation() const;
	//returns the naming "prism"
	const char* getBodyName();
	//creates a prism trough the dialog
	static Body* createByDialog();
private:
	//the refPoint is in the lower front left corner
	Point3D refPoint;
	double width;
	double height;
	double depth;
};

#endif // !PRISM_H