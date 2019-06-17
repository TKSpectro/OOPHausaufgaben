#include "Point3D.h"

Point3D::Point3D(double xValue, double yValue, double zValue)
	: x(xValue), y(yValue), z(zValue)
{
}

Point3D::Point3D(Length& _x, Length& _y, Length& _z)
	: x(_x.getValue()), y(_y.getValue()), z(_z.getValue())
{

}


Point3D::~Point3D()
{
}

double Point3D::getX(Length::Unit unit) const
{
	return this->x;
}

double Point3D::getY(Length::Unit unit) const
{
	return this->y;
}

double Point3D::getZ(Length::Unit unit) const
{
	return this->z;
}

Point3D Point3D::getLocation() const
{
	return Point3D(x, y, z);
}
