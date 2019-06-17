#define _CRT_SECURE_NO_WARNINGS
#ifndef POINT2D_H
#define POINT2D_H
#include"Drawer2D.h"
#include"Vector2D.h"
#include<math.h>
#include<cmath>

class BoundingBox2D;

class Point2D
{
public:
	Point2D(double x = 0.0, double y = 0.0);
	~Point2D();
	double getX() const;
	double getY() const;
	bool isValid() const;
	Point2D add(const Vector2D& vect) const;
	Vector2D getDifference(const Point2D& other) const;
	double getDistance() const;
	double getDistance(const Point2D& other) const;
	void moveBy(const Vector2D& delta);
	void moveBy(double deltaX, double deltaY);
	void moveTo(double newX, double newY);
	BoundingBox2D getBounds() const;
	void draw(Drawer2D& drawer) const;
private:
	double x;
	double y;
};
#endif // !POINT2D_H