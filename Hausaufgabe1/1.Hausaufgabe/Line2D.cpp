#include "Line2D.h"
#include<cmath>
#include<iostream>
#include"Vector2D.h"


Line2D::Line2D()
{
}

Line2D::Line2D(const Point2D& p1, const Point2D& p2)
	:p_Start(p1.getX(), p1.getY()), p_End(p2.getX(), p2.getY())
{
}


Line2D::~Line2D()
{
}

Point2D Line2D::getStart() const
{
	return Point2D(this->p_Start.getX(), this->p_Start.getY());
}

Point2D Line2D::getEnd() const
{
	return Point2D(this->p_End.getX(), this->p_End.getY());
}

//https://stackoverflow.com/questions/17195055/calculate-a-perpendicular-offset-from-a-diagonal-line
Point2D Line2D::getPointAt(double offset) const
{
	double factor = offset / this->getLength();
	if (factor > 1)
	{
		std::cout << "offset zu groß";
	}
	Vector2D vector(this->p_End.getX() - this->p_Start.getX(), this->p_End.getY() - this->p_Start.getY());
	return Point2D(this->p_Start.getX() + (factor * vector.getX()), this->p_Start.getY() + (factor * vector.getY()));
}

double Line2D::getLength() const
{
	return this->p_Start.getDistance(this->p_End);
}

Line2D Line2D::add(const Vector2D & vect) const
{
	return Line2D(this->p_Start, this->p_End.add(vect));
}

Vector2D Line2D::getVector() const
{
	return p_End.getDifference(p_Start);
}

void Line2D::moveBy(const Vector2D & offs)
{
	this->p_Start.moveBy(offs);
	this->p_End.moveBy(offs);
}

void Line2D::moveBy(double deltaX, double deltaY)
{
	this->p_Start.moveBy(deltaX, deltaY);
	this->p_End.moveBy(deltaX, deltaY);
}

//if the line cross each other then the return is 0
double Line2D::getDistance(const Line2D & other) const
{
	if (this->isParallel(other))
	{
		double distance;

		distance = this->getDistance(other.getEnd());

		if ((this->getDistance(other.getStart()) < distance))
			distance = this->getDistance(other.getStart());

		if ((other.getDistance(this->getEnd()) < distance))
			distance = other.getDistance(this->getEnd());

		if ((other.getDistance(this->getStart()) < distance))
			distance = other.getDistance(this->getStart());

		return distance;
	}
	else
	{
		return 0;
	}
	return this->p_Start.getDistance(other.p_Start), this->p_End.getDistance(other.p_End);
}

//https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line -> Line defined by two points
double Line2D::getDistance(const Point2D & other) const
{
	Vector2D vectorDifference = this->p_End.getDifference(this->p_Start);
	double a = vectorDifference.getY() * other.getX();
	double b = vectorDifference.getX() * other.getY();
	double c = -a - b;
	return abs(a - b + c) / this->p_Start.getDistance(this->p_End);
}

BoundingBox2D Line2D::getBounds() const
{
	Point2D p1(this->p_Start);
	return BoundingBox2D(p1, this->p_Start.getDistance(Point2D(this->p_End.getX(), this->p_Start.getY())), this->p_Start.getDistance(Point2D(this->p_Start.getX(), this->p_End.getY())));
}

bool Line2D::isParallel(const Line2D & line) const
{
	//TODO Funktionen nutzen

	double a1 = this->p_End.getY() - this->p_Start.getY();
	double b1 = this->p_Start.getX() - this->p_End.getX();
	double c1 = a1 * (this->p_Start.getX()) + b1 * (this->p_Start.getY());

	double a2 = line.p_End.getY() - line.p_Start.getY();
	double b2 = line.p_Start.getX() - line.p_End.getX();
	double c2 = a2 * (line.p_Start.getX()) + b2 * line.p_Start.getY();

	double determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}