#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <math.h>

Sphere::Sphere(Point3D refPoint, double radius, Length::Unit unit)
	:refPoint(refPoint), radius(radius)
{
	this->Counter++;
}

Sphere::~Sphere()
{
}

double Sphere::getVolume(Length::Unit unit) const
{
	return Length((4 / 3.0) * (M_PI)* pow(this->radius, 3),unit).getValue();
}

double Sphere::getSurface(Length::Unit unit) const
{
	return Length(4 * M_PI * pow(this->radius, 2),unit).getValue();
}

Point3D Sphere::getLocation() const
{
	return this->refPoint;
}

const char* Sphere::getBodyName()
{
	return "sphere";
}

Body* Sphere::createByDialog()
{
	double radius = 0.0;
	cout << "create sphere:" << endl << endl;
	
	cout << "Input the radius: \t";
	while(radius == 0)
	{
		cin >> radius;
		if(radius == 0)
			cout << "radius cant be 0" << endl;
	}
	radius = abs(radius);

	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - middle of the sphere" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	Sphere* t_sphere = new Sphere(Point3D(x,y,z), radius);
	return t_sphere;
}
