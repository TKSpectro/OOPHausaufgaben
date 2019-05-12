#pragma once

#define _USE_MATH_DEFINES
#include<math.h>



class Vector2D
{

public:
	Vector2D(double deltax = 0.0, double deltay = 0.0);
	~Vector2D();
	double getX() const;									//Wurde getestet und funktioniert
	double getY() const;									//Wurde getestet und funktioniert
	Vector2D add(const Vector2D& other) const;				//Wurde getestet und funktioniert
	Vector2D subtract(const Vector2D& other) const;			//Wurde getestet und funktioniert
	double getLength() const;								//Wurde getestet und funktioniert
	double getOrientation() const;							//Wurde getestet und funktioniert
	double multiply(const Vector2D& other) const;			//Wurde getestet und funktioniert

private:
	double deltaX;
	double deltaY;
};

