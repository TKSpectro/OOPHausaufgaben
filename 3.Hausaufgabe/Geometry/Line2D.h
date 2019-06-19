#pragma once
#ifndef LINE2D_H
#define LINE2D_H
/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * Einfache Linie (Strecke) im zweidimensionalen reellen Raum (Zeichenebene)
 *
 * Historie:
 * Datum		Beschreibung
 * 23.05.2019	Erste Version
 * 24.05.2019	Vererbungsproblem mit Methoden getCrosspoint und intersects gelöst.
 */

#include "Point2D.h"
#include "BoundingBox2D.h"

// Class represents a simple straight line (stretch) in a two-demensional plane
class Line2D
{
public:
	Line2D(const Point2D& p1, const Point2D& p2);
	virtual ~Line2D();
	// Returns (a copy of) the starting point of this line stretch
	Point2D getStart() const;
	// Returns (a copy of) the ending point of this line stretch
	Point2D getEnd() const;
	// Returns a (possibly fictitious) point along this line. It will be marked invalid
	// if it is not situated between start and end point (but extrapolated).
	virtual Point2D getPointAt(double offsetFromStart) const;
	// Returns the shortest Cartesian distance to the given point
	virtual double getDistance(const Point2D& point) const;
	// Returns the shortest Cartesian distance to the other line
	// NOTE: If other is a subclass object then consider other.getDistance(*this) as well!
	virtual double getDistance(const Line2D& other) const;
	// Returns a vector from start to end point
	Vector2D getVector() const;
	// Translates this point according to the  given displacement
	virtual void moveBy(const Vector2D& displacement);
	// Translates this point according to the  given displacement
	virtual void moveBy(double deltaX, double deltaY);
	// Returns the length of his line
	virtual double getLength() const;
	// Returns the bounding box of this line
	virtual BoundingBox2D getBounds() const;
	// Draws this line by means of drawer
	virtual void draw(Drawer2D& drawer) const;
	// string conversion operator for self-description
	virtual operator string() const;
	// Checks whether there this is intersecting (or touching) the other line.
	virtual bool intersects(const Line2D& other) const;
protected:
	// staring point of this line
	Point2D start;
	// ending point of this line
	Point2D end;
	// Returns true if point (assumed to be situated on this line) lies between start and end point.
	// Note: it is not checked whether the point is located on the (prolongated) line at all!
	bool contains(const Point2D& point) const;
	// Helper method returning te minimum of two double values (like the macro min but without computing arguments twice)
	static double min(double a, double b);
private:
	// Constructs the virtual crosspoint with other line. The point may be outside the stretches of
	// either line and will only be marked invalid if it doesn't exist or isn't unique. Consider
	// checking with one of the methods contains or intersects.
	// NOTE: This method is a nice example for trouble you may get into with inheritance: The method
	// is very helpful for Line2D, provided no one passes a Polyline2D as argument! On Polyline2D it
	// wouldn't even make sense to override the method - its signature is not adequate (Polylines may
	// have several intersections). So it is made private rather than protected and not virtual.
	Point2D getCrosspoint(const Line2D& other) const;
};

// stream output operator for self-description
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& str, const Line2D& line);

#endif /*LINE2D_H*/