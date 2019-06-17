#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Point2D.h"
#include<math.h>
#include"BoundingBox2D.h"
#include"Drawer2D.h"
class Line2D
{
public:
	Line2D();
	Line2D(const Point2D& p1, const Point2D& P2);
	~Line2D();
	virtual Point2D getStart() const;
	virtual Point2D getEnd() const;
	Point2D getPointAt(double offset) const;
	virtual double getLength() const;
	Vector2D getVector() const;
	void moveBy(const Vector2D& offs);
	void moveBy(double deltaX, double deltaY);
	bool isParallel(const Line2D& line) const;
	virtual double getDistance(const Line2D& other) const;
	virtual double getDistance(const Point2D& other) const;
	virtual BoundingBox2D getBounds() const;
	bool PointIsOnLine(Point2D& other) const;
	void draw(Drawer2D& drawer) const;
protected:
	Point2D p_Start, p_End;
};

