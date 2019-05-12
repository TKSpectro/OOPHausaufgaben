#include "Point2D.h"



Point2D::Point2D(double x, double y) 
	:x(x), y(y)
{
	this->isValid = true;
	if (isnan(this->x) == true && isnan(this->y) == true)
		this->isValid = false;

}


Point2D::~Point2D()
{
}

double Point2D::getX() const
{
	return this->x;
}

double Point2D::getY() const
{
	return this->y;
}

bool Point2D::isValid() const
{
	this->isValid;
}

Point2D Point2D::add(const Vector2D& vect) const
{
	return Point2D(this->x + vect.getX(), this->y + vect.getY());
}

Vector2D Point2D::getDifference(const Point2D& other) const
{ 

		return Vector2D (this->x - other.getX(), this->y - other.getY());
	
}

double Point2D::getDistance() const
{
	
	return this ->getX(),this->getY();
}

double Point2D::getDistance(const Point2D& other) const
{
	return sqrt(pow(this->x-other.x,2)+pow(this->x-other.x,2));
}

void Point2D::moveBy(const Vector2D& delta)
{
	this->x += delta.getX();
	this->y += delta.getY();
}

void Point2D::moveBy(double deltaX, double deltaY)
{
	this->x += deltaX;
	this->y += deltaY;
}

void Point2D::moveTo(double newX, double newY)
{
	this->x = newX;
	this->y = newY;
}

BoundingBox2D Point2D::getBouSnds() const
{
	return BoundingBox2D();
}
