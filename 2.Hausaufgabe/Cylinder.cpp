#include "Cylinder.h"

Cylinder::Cylinder(Point3D refPoint, double radius, double height, Length::Unit unit)
	:refPoint(refPoint), radius(Length(radius).getValue()), height(Length(height).getValue())
{
	this->Counter++;
}

Cylinder::~Cylinder()
{
}

double Cylinder::getVolume(Length::Unit unit ) const
{
	return Length(M_PI * pow(radius, 2) * height,unit).getValue();
}

double Cylinder::getSurface(Length::Unit unit) const
{
	return Length(2 * M_PI * pow(radius, 2) + 2 * M_PI * radius * height,unit).getValue();
}

Point3D Cylinder::getLocation() const
{
	return Point3D(this->refPoint.getX(), this->refPoint.getY() + height / 2, this->refPoint.getZ());
}

const char* Cylinder::getBodyName()
{
	return "cylinder";
}

Body* Cylinder::createByDialog()
{
	double radius = 0.0; double height = 0.0;
	cout << "create cylinder:" << endl << endl;

	cout << "Input the radius: \t";
	while(radius == 0)
	{
		cin >> radius;
		if(radius == 0)
			cout << "radius cant be 0";
	}
	radius = abs(radius);

	cout << "Input the height: \t";
	while(height == 0)
	{
		cin >> height;
		if(height == 0)
			cout << "height cant be 0";
	}	
	height = abs(height);
	
	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - center of circle" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	Cylinder* t_cylinder = new Cylinder(Point3D(x,y,z), radius, height, Length::METRE);
	return t_cylinder;
}
