#include"Line2D.h"
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

Point2D Line2D::getPointAt(double offset) const
{
	double factor = offset / this->getLength();
	if(offset > this->getLength())
	{
		return Point2D(pow(10, 10000), pow(10, 100000));
	}
	Vector2D vector(this->p_End.getX() - this->p_Start.getX(), this->p_End.getY() - this->p_Start.getY());
	return Point2D(this->p_Start.getX() + (factor * vector.getX()), this->p_Start.getY() + (factor * vector.getY()));
}

double Line2D::getLength() const
{
	return this->p_Start.getDistance(this->p_End);
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
		return 0;
	return this->p_Start.getDistance(other.p_Start), this->p_End.getDistance(other.p_End);
}

double Line2D::getDistance(const Point2D & other) const
{
	double Distance = 0.0;
	Vector2D x0(p_Start.getX(), p_Start.getY());
	Vector2D a(this->getVector());
	Vector2D x1(other.getX(), other.getY());
	double t = a.multiply(x0.subtract(x1))/a.multiply(a);
	Vector2D T_a(a.getX() * t, a.getY() * t);
	Vector2D Length=T_a.add(x0.subtract(x1));

	Point2D isPointonLine = other;
	isPointonLine.moveBy(Length);
	bool P_onLine = this->PointIsOnLine(isPointonLine);

	if (P_onLine == false)
	{
		if (this->getStart().getDistance(other) > this->getEnd().getDistance(other))
			Distance = this->getEnd().getDistance(other);
		else
			Distance = this->getStart().getDistance(other);
	}
	else
		Distance = Length.getLength();
	return Distance;
}

BoundingBox2D Line2D::getBounds() const
{
	Point2D p1(this->p_Start);
	return BoundingBox2D(p1, this->p_Start.getDistance(Point2D(this->p_End.getX(), this->p_Start.getY())), this->p_Start.getDistance(Point2D(this->p_Start.getX(), this->p_End.getY())));
}

bool Line2D::PointIsOnLine(Point2D& other) const
{
	bool PointIsOnLine = false;
	Line2D l1(p_Start, other);
	Line2D l2(p_End, other);
	Vector2D Start_vec = l1.getVector();
	Vector2D End_vec = l2.getVector();
	if ((Start_vec.getLength() <= this->getLength()) && (End_vec.getLength() <= this->getLength()))
		PointIsOnLine = true;

	return PointIsOnLine;
}

bool Line2D::isParallel(const Line2D & line) const
{
	double a1 = this->p_End.getY() - this->p_Start.getY();
	double b1 = this->p_Start.getX() - this->p_End.getX();
	double c1 = a1 * (this->p_Start.getX()) + b1 * (this->p_Start.getY());

	double a2 = line.p_End.getY() - line.p_Start.getY();
	double b2 = line.p_Start.getX() - line.p_End.getX();
	double c2 = a2 * (line.p_Start.getX()) + b2 * line.p_Start.getY();

	double determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)
		return true;
	else
		return false;
}

void Line2D::draw(Drawer2D& drawer) const
{
	drawer.DrawLine(p_Start.getX(), p_Start.getY(), p_End.getX(), p_End.getY());
}