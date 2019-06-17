#define _USE_MATH_DEFINES
#include "Cone.h"
#include <math.h>


Cone::Cone(Point3D refPoint, double radius, double height, Length::Unit uni)
	: refPoint(refPoint), radius(Length(radius, uni).getValue()), height(Length(height, uni).getValue())
{
	this->Counter++;
}

Cone::~Cone()
{
}

double Cone::getVolume(Length::Unit unit) const
{
	return Length(M_PI * pow(radius, 2) * (this->height / 4.0)).getValue();
}

double Cone::getSurface(Length::Unit unit) const
{
	return Length(M_PI * radius * (radius + sqrt(pow(height, 2) + pow(radius, 2))), unit).getValue();
}

Point3D Cone::getLocation() const
{
	double centerGravity = this->height / 4;
	return Point3D(this->refPoint.getX(), this->refPoint.getY() + centerGravity, this->refPoint.getZ());
}

const char* Cone::getBodyName()
{
	return "cone";
}

Body* Cone::createByDialog()
{
	double radius = 0.0; double height = 0.0;
	cout << "create cone: " << endl << endl;

	cout << "Input the radius: \t";
	while(radius == 0.0)
	{
		cin >> radius;
		if(radius == 0.0)
			cout << "radius cant be 0" << endl;
	}
	radius = abs(radius);

	cout << "Input the height: \t";
	while(height == 0.0)
	{
		cin >> height;
		if(height == 0.0)
			cout << "height cant be 0" << endl;
	}
	height = abs(height);
	
	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - center of the bottom circle" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;
	
	Cone* t_cone = new Cone(Point3D(x,y,z),radius, height, Length::METRE);
	return t_cone;
}
