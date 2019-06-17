#define _CRT_SECURE_NO_WARNINGS
#ifndef BOUNDINGBOX2D_H
#define BOUNDINGBOX2D_H
#include"Drawer2D.h"

class Point2D;

class BoundingBox2D
{
public:
	BoundingBox2D();
	BoundingBox2D(Point2D& start, double width, double heigth);
	~BoundingBox2D();
	double getWidth() const;
	double getHeigth() const;
	Point2D getStartPoint() const;
	void uniteWith(const BoundingBox2D& other);
	void draw(Drawer2D& drawer) const;
private:
	Point2D* StartPoint;
	double Width;
	double Heigth;
};

#endif // !BOUNDINGBOX2D_H