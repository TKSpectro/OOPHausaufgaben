#ifndef POINT2D_H
#define POINT2D_H

#include"Vector2D.h"
//#include"BoundingBox2D.h"
#include <math.h>
#include <cmath>

class BoundingBox2D;

class Point2D
{
public:
	Point2D(double x = 0.0, double y = 0.0);
	~Point2D();
	double getX() const;								//Wurde getestet und funktioniert
	double getY() const;								//Wurde getestet und funktioniert
	bool isValid() const;								//TODO
	Point2D add(const Vector2D& vect) const;			//Wurde getestet und funktioniert
	Vector2D getDifference(const Point2D& other) const;	//Wurde getestet und funktioniert
	double getDistance() const;							//Wurde getestet und funktioniert
	double getDistance(const Point2D& other) const;		//Wurde getestet und funktioniert
	void moveBy(const Vector2D& delta);					//Wurde getestet und funktioniert
	void moveBy(double deltaX, double deltaY);			//Wurde getestet und funktioniert
	void moveTo(double newX, double newY);				//Wurde getestet und funktioniert
	BoundingBox2D getBounds() const;					//Wurde getestet und funktioniert nicht -> Startpoint stimmt nicht
private:
	double x;
	double y;
//	bool Valid;

};

#endif // !POINT2D_H