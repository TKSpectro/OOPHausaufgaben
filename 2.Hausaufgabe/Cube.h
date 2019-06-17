#pragma once
#ifndef CUBE_H
#define CUBE_H
#include "Point3D.h"
#include "Body.h"


/*wenn man eine Seperate-ID für jede Körperart machen will, soll man einen einzelnen Zähler in jeder Klasse machen*/

class Cube:
	public Body
{
public:
	//Test for separate ID
	static int zähler;
	//unique ID for every new Cube
	const int Cube_ID = this->Counter;
	Cube(Point3D refPoint, double sideSize,Length::Unit unit = Length::METRE);
	~Cube();
	//returns the volume of the cube
	double getVolume(Length::Unit unit= Length::METRE) const;
	//returns the surface of the cube
	double getSurface(Length::Unit unit = Length::METRE) const;
	//returns the center of gravity
	Point3D getLocation() const;
	//returns the naming "cube"
	const char* getBodyName();
	//creates a cube trough the dialog
	static Body* createByDialog();
private:
	//the refPoint is in the lower front left corner
	Point3D refPoint;
	double size;
	
};

#endif // !CUBE_H