#include "Tower.h"

Tower::Tower(Point3D refPoint, double radius, double coneHeight, double cylinderHeight, Length::Unit unit)
	:refPoint(refPoint), radius(radius), coneHeight(coneHeight), cylinderHeight(cylinderHeight)
{
	Cylinder t_Cylinder(refPoint, radius, cylinderHeight, unit);
	Cone t_Cone(refPoint, radius, coneHeight, unit);

	Point3D t_ConeRefPoint = t_Cone.getLocation();
	Point3D t_CylinderRefPoint = t_Cylinder.getLocation();

	double center = (t_Cylinder.getVolume() * t_CylinderRefPoint.getY() + t_ConeRefPoint.getY() * t_Cone.getVolume()) / (t_Cylinder.getVolume() + t_Cone.getVolume());

	this->refPoint = Point3D(this->refPoint.getX(), this->refPoint.getY() + center, this->refPoint.getZ());

	this->Counter++;
}

Tower::~Tower()
{
}

double Tower::getVolume(Length::Unit unit) const
{
	double cylVol = Cylinder(Point3D(0, 0, 0), this->radius, this->cylinderHeight).getVolume();
	double conVol = Cone(Point3D(0, 0, 0), this->radius, this->coneHeight).getVolume();
	double vol = cylVol + conVol;
	return Length(vol, unit).getValue();

}

double Tower::getSurface(Length::Unit unit) const
{
	double cylArea = Cylinder(Point3D(0, 0, 0), this->radius, this->cylinderHeight).getSurface();
	double conArea = Cone(Point3D(0, 0, 0), this->radius, this->coneHeight).getSurface();
	//remove the are where they would sit on each other
	double area = (cylArea + conArea) - 2 * (M_PI * pow(this->radius, 2));
	return Length(area, unit).getValue();
}

Point3D Tower::getLocation() const
{
	return Point3D(this->refPoint.getX(), this->refPoint.getY() + (this->cylinderHeight / 2) + (this->coneHeight / 4), this->refPoint.getZ());
}

const char* Tower::getBodyName()
{
	return "tower";
}

Body* Tower::createByDialog()
{
	double radius = 0.0; double coneHeight = 0.0; double cylinderHeight = 0.0;
	cout << "create tower:" << endl << endl;

	cout << "Input the radius of the tower: \t";
	while(radius == 0)
	{
		cin >> radius;
		if(radius == 0)
			cout << "radius cant be 0";
	}
	radius = abs(radius);

	cout << "Input the height of the tower (without the cone): \t";
	while(cylinderHeight == 0)
	{
		cin >> cylinderHeight;
		if(cylinderHeight == 0)
			cout << "cylinderHeight cant be 0";
	}
	cylinderHeight = abs(cylinderHeight);

	while(coneHeight == 0)
	{
		cin >> coneHeight;
		if(coneHeight == 0)
			cout << "coneHeight cant be 0";
	}
	coneHeight = abs(coneHeight);

	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - center of the circle on the bottom" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	Tower* t_tower = new Tower(Point3D(x, y, z), radius, coneHeight, cylinderHeight, Length::METRE);
	return t_tower;
}
