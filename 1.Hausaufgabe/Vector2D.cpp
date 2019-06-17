#include"Vector2D.h"
#include"Point2D.h"

Vector2D::Vector2D(double deltax, double deltay)
	:deltaX(deltax), deltaY(deltay)
{
}

Vector2D::~Vector2D()
{
}

double Vector2D::getX() const
{
	return this->deltaX;
}

double Vector2D::getY() const
{
	return this->deltaY;
}

Vector2D Vector2D::add(const Vector2D& other) const
{
	return Vector2D(this->deltaX + other.deltaX, this->deltaY + other.deltaY);
}

Vector2D Vector2D::subtract(const Vector2D& other) const
{
	return Vector2D(this->deltaX - other.deltaX, this->deltaY - other.deltaY);
}

double Vector2D::getLength() const
{
	return sqrt((this->deltaX * this->deltaX) + (this->deltaY * this->deltaY));
}

double Vector2D::getOrientation() const
{
	double alpha = atan(this->deltaX / this->deltaY);
	if (this->deltaX < 0)
		alpha += (this->deltaY >= 0 ? M_PI : - M_PI);
	return alpha;
}

double Vector2D::multiply(const Vector2D & other) const
{
	return this->deltaX * other.deltaX + this->deltaY * other.deltaY;
}

