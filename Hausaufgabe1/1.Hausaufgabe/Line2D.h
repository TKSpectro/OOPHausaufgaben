#pragma once
#include "Point2D.h"
#include<math.h>
#include"BoundingBox2D.h"
class Line2D
{
public:
	Line2D();
	Line2D(const Point2D& p1, const Point2D& P2);
	~Line2D();
	Point2D getStart() const;						//Wurde getestet und funktioniert
	Point2D getEnd() const;							//Wurde getestet und funktioniert
	Point2D getPointAt(double offset) const;		//Wurde getestet und funktioniert
	virtual double getLength() const;				//Wurde getestet und funktioniert
	Line2D add(const Vector2D& vect) const;			//Wurde getestet und funktioniert
	Vector2D getVector() const;						//Wurde getestet und funktioniert
	void moveBy(const Vector2D& offs);				//Wurde getestet und funktioniert
	void moveBy(double deltaX, double deltaY);		//Wurde getestet und funktioniert
	bool isParallel(const Line2D& line) const;		//Wurde getestet und funktioniert
	double getDistance(const Line2D& other) const;	//Wurde getestet und funktioniert
	double getDistance(const Point2D& other) const;	//Wurde getestet und funktioniert nicht -> Distanz stimmt nicht
	BoundingBox2D getBounds() const;				//Wurde getestet und funktioniert nicht -> Startpunkt ist falsch


protected:

	Point2D p_Start, p_End;

};

