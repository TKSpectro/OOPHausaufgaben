#pragma once
#ifndef POINT3D_H
#define POINT3D_H
#include "Length.h"
class Point3D
{
public:
	Point3D(double xValue = 0, double yValue = 0, double zValue = 0);
	Point3D(Length& x, Length& y, Length& z);
	~Point3D();
	double getX(Length::Unit unit=Length::METRE) const;
	double getY(Length::Unit unit = Length::METRE) const;
	double getZ(Length::Unit unit = Length::METRE) const;
	Point3D getLocation() const;
private:
	double x;
	double y;
	double z;
};

#endif // !POINT3D_H