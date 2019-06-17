#include "Prism.h"
#define _USE_MATH_DEFINES
#include <math.h>


Prism::Prism(Point3D refPoint, double width, double height, double depth, Length::Unit unit)
	:refPoint(refPoint), width(Length(width).getValue()), height(Length(height).getValue()), depth(Length(depth).getValue())
{
	this->Counter++;
}

Prism::~Prism()
{
}

double Prism::getVolume(Length::Unit unit) const
{
	return Length(this->width * this->height * this->depth * 0.5).getValue();
}

double Prism::getSurface(Length::Unit unit) const
{
	double sideSize = sqrt(pow(this->width / 2, 2) + pow(this->height, 2));
	return (this->width * this->depth) + (2 * this->depth * sideSize) + (height * width);
}

Point3D Prism::getLocation() const
{
	return Point3D(this->refPoint.getX() + this->depth / 2, this->refPoint.getY() + this->width / 2, this->refPoint.getZ() + this->height / 3);
}

const char* Prism::getBodyName()
{
	return "prism";
}

Body* Prism::createByDialog()
{	
	cout << "create prism: " << endl << endl;

	double width = 0.0; double depth = 0.0; double height = 0.0;
	cout << "Input the width: \t";
	while(width == 0.0)
	{
		cin >> width;
		if(width == 0.0)
			cout << "width cant be 0" << endl;
	}
	width = abs(width);

	cout << "Input the depth: \t";
	while(depth == 0.0)
	{
		cin >> depth;
		if(depth == 0.0)
			cout << "depth cant be 0" << endl;
	}
	depth = abs(depth);

	cout << "Input the height: \t";
	while(height == 0.0)
	{
		cin >> height;
		if(height == 0.0)
			cout << "height cant be 0" << endl;
	}
	height = abs(height);

	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - lower front left corner" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	Prism* t_prism = new Prism(Point3D(x,y,z), width, height, depth);
	return t_prism;
}
