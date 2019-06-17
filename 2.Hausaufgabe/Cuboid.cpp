#include "Cuboid.h"


Cuboid::Cuboid(Point3D refPoint, double xLength, double yLength, double zLength, Length::Unit unit)
	:refPoint(refPoint), xLength(Length(xLength).getValue()), yLength(Length(yLength).getValue()), zLength(Length(zLength).getValue())
{
	this->Counter++;
}

Cuboid::~Cuboid()
{
}

double Cuboid::getVolume(Length::Unit unit) const
{
	return Length(xLength * yLength * zLength,unit).getValue();
}


double Cuboid::getSurface(Length::Unit unit) const
{
	return Length(2 * ((xLength * yLength) + (xLength * zLength) + (yLength * zLength)),unit).getValue();
}

Point3D Cuboid::getLocation() const
{
	return Point3D(this->refPoint.getX() + this->xLength / 2, this->refPoint.getY() + this->yLength / 2, this->refPoint.getZ() + this->zLength / 2);
}

const char* Cuboid::getBodyName()
{
	return "cuboid";
}

Body* Cuboid::createByDialog()
{
	
	double xSize = 0.0; double ySize = 0.0;double zSize = 0.0;
	cout << "create cuboid:" << endl << endl;

	cout << "Input the xSize: \t";
	while(xSize == 0.0)
	{
		cin >> xSize;
		if(xSize == 0.0)
			cout << "Size cant be 0";
	}
	xSize = abs(xSize);

	cout << "Input the ySize: \t";
	while(ySize == 0.0)
	{
		cin >> ySize;
		if(ySize == 0.0)
			cout << "Size cant be 0";
	}
	ySize = abs(ySize);

	cout << "Input the zSize: \t";
	while(zSize == 0.0)
	{
		cin >> zSize;
		if(zSize == 0.0)
			cout << "Size cant be 0";
	}
	zSize = abs(zSize);

	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - lower front left corner" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	Cuboid* t_cuboid = new Cuboid(Point3D(x,y,z), xSize, ySize, zSize, Length::METRE);
	return t_cuboid;
}
