#pragma once

#include "Line2D.h"
#include "Point2D.h"
#include <vector>
#include <string>
#include <iterator>

using namespace std;
using std::vector;

vector<Point2D>::iterator it;

class Point2D;
class Polyline2D: public Line2D
{
public: 
	Polyline2D(const Point2D& StartPoint,const Point2D& EndPoint);
	~Polyline2D();
	double getLength() const;
	// fragen ob es logisch ist
	bool isLine2D();
	Point2D getPoint(unsigned short number) const;
	unsigned short getNumberOfPoints() const;
	bool insertPoint(const Point2D& pt, unsigned short before);
	bool removePoint(unsigned short number);
	bool isSelfIntersecting() const;
private:
	vector<Point2D> Points;
};

