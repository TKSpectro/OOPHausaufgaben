#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Line2D.h"
#include"Point2D.h"
#include<vector>
using std::vector;
using namespace std;

class Polyline2D: public Line2D
{
public: 
	Polyline2D( vector<Point2D> Points, Point2D& StartPoint, Point2D& EndPoint);
	~Polyline2D();
	bool isLine2D();
	Point2D getPoint(unsigned short number) const;
	unsigned short getNumberOfPoints() const;
	bool insertPoint(const Point2D& pt, unsigned short before);
	bool removePoint(unsigned short number);
	bool isSelfIntersecting() const;
	void draw(Drawer2D& drawer) const;

	virtual Point2D getStart();
	virtual Point2D getEnd();
	virtual double getLength() const;
	virtual double getDistance(const Point2D &other) const;
	virtual BoundingBox2D getBounds() const;
private:
	vector<Point2D> _Points;
};

