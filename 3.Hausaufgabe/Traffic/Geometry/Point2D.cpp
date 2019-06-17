/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * Punkt im zweidimensionalen reellen Raum (Zeichenebene)
 *
 * Historie:
 * Datum		Beschreibung
 * 23.05.2019	Erste Version
 */
#include "Point2D.h"
#include <cmath>
#include <limits>
#include <sstream>

const double Point2D::EQUALITY_THRESHOLD = 1E-250;

Point2D::Point2D(double coordX, double coordY, bool valid)
: x(coordX)
, y(coordY)
, valid(valid)
{
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
	// In pure C we might have used <math.h> macro HUGE_VALD or (double)INFINITY 
	return this->valid
		&& abs(this->x) != std::numeric_limits<double>::infinity()
		&& abs(this->y) != std::numeric_limits<double>::infinity();
}

// Returns a point displaced by vect from this
Point2D Point2D::add(const Vector2D& vec) const
{
	return Point2D(this->x + vec.getX(), this->y + vec.getY());
}

// Returns the cartesian distance between this and other
double Point2D::getDistance(const Point2D& other) const
{
	return getDifference(other).getLength();
	// Alternativ:
	//double deltaX = other.x - this->x;
	//double deltaY = other.y - this->y;
	//return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// Returns the difference vector between this and other
Vector2D Point2D::getDifference(const Point2D& other) const
{
	return Vector2D(this->x - other.x, this->y - other.y);
}

// Tranlates this point according to the  given displacement
void Point2D::moveBy(const Vector2D& displacement)
{
	this->x += displacement.getX();
	this->y += displacement.getY();
}

// Translates this point according to the  given displacement
void Point2D::moveBy(double deltaX, double deltaY)
{
	this->x += deltaX;
	this->y += deltaY;
}

// Translates this point to the new coordniate location
void Point2D::moveTo(double newX, double newY)
{
	this->x = newX;
	this->y = newY;
}

// Draws this point in the Turtleizer canvas
void Point2D::draw(Drawer2D& drawer) const
{
	drawer.drawPoint(x, y);
}

// Returns a (trivial) bounding box for this point
BoundingBox2D Point2D::getBounds() const
{
	return BoundingBox2D(x, y, x, y);
}

Point2D::operator std::string() const
{
	std::ostringstream str;
	str << "Point2D" << "(" << (this->valid ? "" : "INVALID, ") << this->x << "," << this->y << ")";
	return str.str();
}

bool Point2D::operator==(const Point2D & other) const
{
	return abs(this->x - other.x) < EQUALITY_THRESHOLD && abs(this->y - other.y) < EQUALITY_THRESHOLD;
}

//bool Point2D::operator!=(const Point2D & other) const
//{
//	return !(*this == other);
//}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& str, const Point2D& point)
{
	str << string(point);
	return str;
}
