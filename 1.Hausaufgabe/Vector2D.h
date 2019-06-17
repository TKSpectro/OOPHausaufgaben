#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include<math.h>

class Vector2D
{
public:
	Vector2D(double deltax = 0.0, double deltay = 0.0);
	~Vector2D();
	double getX() const;
	double getY() const;
	Vector2D add(const Vector2D& other) const;
	Vector2D subtract(const Vector2D& other) const;
	double getLength() const;
	double getOrientation() const;
	double multiply(const Vector2D& other) const;
private:
	double deltaX;
	double deltaY;
};

