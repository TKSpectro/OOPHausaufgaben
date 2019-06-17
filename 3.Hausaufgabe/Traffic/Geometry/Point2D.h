#pragma
#ifndef POINT2D_H
#define POINT2D_H
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

#include "Vector2D.h"
#include "Drawer2D.h"
#include "BoundingBox2D.h"
#include <ostream>
#include <string>
#include <utility>
using namespace std::rel_ops;

using std::string;

// Class represents a simple point in a two-dimensional plane
class Point2D
{
public:
	// Tolerated difference between coordinates regarded as equal
	static const double EQUALITY_THRESHOLD;
	// Creates a point at position (coordX, coordY), which will be marked invalid if valid = false
	// Making one of the cordinates infinite also invalidates the point (see isValid()).
	Point2D(double coordX = 0.0, double coordY = 0.0, bool valid = true);
	~Point2D();
	// Returns the actual X coordinate
	double getX() const;
	// Returns the acual Y coordinate
	double getY() const;
	// Indicates whether this point is valid at all
	bool isValid() const;
	// Returns a point displaced by vect from this
	Point2D add(const Vector2D& vec) const;
	// Returns the difference vector between this and other
	Vector2D getDifference(const Point2D& other) const;
	// Returns the cartesian distance between this and other
	double getDistance(const Point2D& other = Point2D(0,0)) const;
	// Translates this point according to the  given displacement
	void moveBy(const Vector2D& displacement);
	// Translates this point according to the  given displacement
	void moveBy(double deltaX, double deltaY);
	// Translates this point to the new coordniate location
	void moveTo(double newX, double newY);
	// Returns a (trivial) bounding box for this point
	BoundingBox2D getBounds() const;
	// Draws this point in the Turtleizer canvas
	void draw(Drawer2D& drawer) const;
	// string conversion operator for self-description
	operator std::string() const;
	// Coordinate comparison
	bool operator==(const Point2D& other) const;
	//bool operator!=(const Point2D& other) const;
private:
	// Coordinates
	double x, y;
	// Validity
	bool valid;
};

// stream output operator to facilitate debugging
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& str, const Point2D& point);

#endif /*POINT_2D*/