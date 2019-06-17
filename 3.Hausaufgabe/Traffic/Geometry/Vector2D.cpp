/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * (Nicht ortsfester) Vektor im zweidimensionalen reellen Raum (Zeichenebene)
 *
 * Historie:
 * Datum		Beschreibung
 * 23.05.2029	Erste Version
 */
#define _USE_MATH_DEFINES
#include "Vector2D.h"
#include <cmath>
#include <sstream>

Vector2D::Vector2D(double xDiffOrLength, double yDiffOrAngle, bool asCoordDiffs)
: deltaX(xDiffOrLength)
, deltaY(yDiffOrAngle)
{
	if (!asCoordDiffs) {
		deltaX = xDiffOrLength * cos(yDiffOrAngle);
		deltaY = xDiffOrLength * sin(yDiffOrAngle);
	}
}


Vector2D::~Vector2D()
{
}

// Returns the X length
double Vector2D::getX() const
{
	return this->deltaX;
}

// Returns the Y length
double Vector2D::getY() const
{
	return this->deltaY;
}

// Returns the length of the vector
double Vector2D::getLength() const
{
	return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// Returns the angle as mathematic orientation in radians
double Vector2D::getOrientation() const
{
	double quot = this->deltaY / this->deltaX;
	double angle = atan(quot);
	if (this->deltaX < 0) {
		angle += M_PI;
	}
	return angle;
}

// Returns the vectorial sum of this vector and other
Vector2D Vector2D::add(const Vector2D& other) const
{
	return Vector2D(this->deltaX + other.deltaX, this->deltaY + other.deltaY);
}

// Returns the vectorial difference among this vector and other
Vector2D Vector2D::subtract(const Vector2D& other) const
{
	return Vector2D(this->deltaX - other.deltaX, this->deltaY - other.deltaY);
}

// Returns a sclaed vector with saclar factor
Vector2D Vector2D::scale(double factor) const
{
	return Vector2D(this->deltaX * factor, this->deltaY * factor);
}

// Returns the scalar product of this vector and other
double Vector2D::multiply(const Vector2D& other) const
{
	return this->deltaX * other.deltaX + this->deltaY * other.deltaY;
}

Vector2D::operator std::string() const
{
	std::ostringstream str;
	str << "Vector2D" << "(" << this->deltaX << "," << this->deltaY << ")";
	return str.str();
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& str, const Vector2D& vec)
{
	return (str << std::string(vec));
}
