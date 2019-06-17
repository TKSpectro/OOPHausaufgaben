#include"Polyline2D.h"
#include"Point2D.h"
#include<iterator>

vector<Point2D>::iterator it;

Polyline2D::Polyline2D(vector<Point2D> points, Point2D& StartPoint,  Point2D& EndPoint)
{
	for (int i = 0; i < points.size();i++)
	{
		if (points[i].isValid())
			_Points.push_back(points[i]);
	}
	it = _Points.begin();
	_Points.insert(it, StartPoint);
	it = _Points.end();
	_Points.insert(it, EndPoint);
}

Polyline2D::~Polyline2D()
{
}

bool Polyline2D::isLine2D()
{
	if (this->_Points.size() == 2 )
		return true;
	else
		return false;
}

Point2D Polyline2D::getPoint(unsigned short number) const
{
	if (number > _Points.size())
		return Point2D(pow(10, 10000), pow(10, 100000));
	else
	{ 
		for (int i = 0; i < this->_Points.size(); i++)
		{
			if (i == number)
				return _Points[i];
		}
	}
	return Point2D();
}

unsigned short Polyline2D::getNumberOfPoints() const
{
	return  _Points.size();
}

bool Polyline2D::insertPoint(const Point2D & pt, unsigned short before)
{
	if (_Points.size() == 0)
		return false;
	else
	{
		it = _Points.begin();
		advance(it, before);
		it--;
		_Points.insert(it, pt);
	}
	return true;
}

bool Polyline2D::removePoint(unsigned short number)
{
	if (_Points.size() == 0)
		return false;
	else
	{
		advance(it, number);
		_Points.erase(it);
	}
	return true;
}

bool Polyline2D::isSelfIntersecting() const //TODO
{
	for(int i = 0; i < this->_Points.size(); i++)
	{
		Line2D lineToCheck(_Points[i], _Points[i + 1]);
		for(int k = i; k < this->_Points.size(); i++)
		{
			Line2D checkWithLine(_Points[k], _Points[k + 1]);
			if(lineToCheck.getDistance(checkWithLine))
				return true;
		}
	}
	return false;
}

void Polyline2D::draw(Drawer2D& drawer) const
{
	for (int i = 0; i < this->_Points.size() - 1; i++)
	{
		Line2D line(this->_Points[i], this->_Points[i + 1]);
		drawer.DrawLine(line.getStart().getX(),line.getStart().getY(),line.getEnd().getX(),line.getEnd().getY());
	}
}

Point2D Polyline2D::getStart()
{
	if(_Points.size() == 0)
		return Point2D(pow(10, 10000), pow(10, 100000));
	else
		return _Points[0];
}

Point2D Polyline2D::getEnd()
{
	if(_Points.size() == 0)
		return Point2D(pow(10, 10000), pow(10, 100000));
	else
		return _Points[_Points.size() - 1];
}

double Polyline2D::getLength() const
{
	double sum = 0.0;
	for(int i = 0; i < this->_Points.size() - 1; i++)
	{
		Line2D line(this->_Points[i], this->_Points[i + 1]);
		sum += line.getLength();
	}
	return sum;
}

double Polyline2D::getDistance(const Point2D & other) const
{
	double minimalDistance = 0.0;
	for(int i = 0; i < _Points.size() - 1; i++)
	{
		double newDistance = _Points[i].getDistance(other);
		if(newDistance < minimalDistance)
			minimalDistance = newDistance;
	}
	return minimalDistance;
}

BoundingBox2D Polyline2D::getBounds() const
{
	double startPointX = _Points[0].getX();
	double startPointY = _Points[0].getY();
	double maxX = 0.0;
	double maxY = 0.0;
	for(int i = 0; i < _Points.size() - 1; i++)
	{
		if(_Points[i].getX() < startPointX)
			startPointX = _Points[i].getX();
		if(_Points[i].getY() < startPointY)
			startPointY = _Points[i].getY();
		if(_Points[i].getX() > maxX)
			maxX = _Points[i].getX();
		if(_Points[i].getY() < maxY)
			maxY = _Points[i].getY();
	}
	double width = maxX - startPointX;
	double heigth = maxY - startPointY;
	Point2D startPoint(startPointX, startPointY);
	return BoundingBox2D(startPoint, width, heigth);
}