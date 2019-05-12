#include "Line2D.h"
#include<cmath>


Line2D::Line2D()
{
}

Line2D::Line2D(const Point2D& p1, const Point2D& p2)
	:p_start(p1.getX(),p1.getY()), p_End(p2.getX(),p2.getY())
{
}


Line2D::~Line2D()
{
}

Point2D Line2D::getStart() const
{
	return Point2D(this->p_start.getX(), this->p_start.getY());
}

Point2D Line2D::getEnd() const
{
	return Point2D(this->p_End.getX(), this->p_End.getY());
}
//returns a point but when point is not on the line it will return a non valid point
Point2D Line2D::getPointAt(double offset) const
{
	//If not on line return non valid point;
	return Point2D();
}// TODO check the Size of the Line 

double Line2D::getLength() const
{
	return p_start.getDistance(this->p_End);
}

Line2D Line2D::add(const Vector2D& vect) const
{
	return Line2D(this->p_start, this->p_End.add(vect));
}

Vector2D Line2D::getVector() const
{
	return p_start.getDifference(p_End);
}

void Line2D::moveBy(const Vector2D& offs)
{
	this->p_start.moveBy(offs);
	this->p_End.moveBy(offs);
}

void Line2D::moveBy(double deltaX, double deltaY)
{
	this->p_start.moveBy(deltaX, deltaY);
	this->p_End.moveBy(deltaX, deltaY);
}

bool Line2D::isParallel(Line2D line2)
{
	double a1 = this->p_End.getY() - this->p_start.getY();
	double b1 = this->p_start.getX() - this->p_End.getX();
	double c1 = a1 * (this->p_start.getX()) + b1 * (this->p_start.getY());

	double a2 = line2.p_End.getY() - line2.p_start.getY();
	double b2 = line2.p_start.getX() - line2.p_End.getX();
	double c2 = a2 * (line2.p_start.getX()) + b2 * line2.p_start.getY();

	double determinant = a1 * b2 - a2 * b1;

	if(determinant == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double Line2D::getDistance(const Line2D& other) const
{
	Line2D line0;
	bool parallel = this->isParallel(other);
	return this->p_start.getDistance(other.p_start),this->p_End.getDistance(other.p_End);
}

//double Line2D::getDistance(const Point2D& other) const
//{
//	double m = (this->p_End.getDistance(other) + this->getDistance(other) + this->p_End.getDistance(this->p_start)) / 2;
//
//	return sqrt(m*(m- this->p_End.getDistance(other))*(m- this->getDistance(other))*(m- this->p_End.getDistance(this->p_start)));
//} 


//https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line -> Line defined by two points
double Line2D::getDistance(const Point2D &other) const
{
	double result = 0.0;

	result = abs((this->p_End.getY() - this->p_start.getY()) * other.getX() - (this->p_End.getX() - this->p_start.getX()) * other.getY() + this->p_End.getX() * this->p_start.getY() - this->p_End.getY() * this->p_start.getX()) / sqrt(pow(this->p_End.getY() - this->p_start.getY(), 2) + pow(this->p_End.getX() - this->p_start.getX(), 2));

	return result;
}


