#pragma once
#ifndef POLYLINE2D_H
#define POLYLINE2D_H
/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * Polylinie (mehrfach geknickte Linie) im zweidimensionalen reellen Raum (Zeichenebene)
 *
 * Historie:
 * Datum		Beschreibung
 * 23.05.2019	Erste Version
 * 24.05.2019	Vererbungsproblem mit Methode intersects gelöst.
 */

#include "Line2D.h"
#include <deque>

// Class represents a line with possible intermediate points (sharp bends), consisting of straight line segments.
class Polyline2D : public Line2D
{
public:
	Polyline2D(const Point2D& p1, const Point2D& p2);
	Polyline2D(const Point2D& p1, const Point2D& p2, unsigned int nInterPoints, Point2D interPoints[]);
	//Polyline2D(const Polyline2D& other);
	~Polyline2D();
	// Returns a (possibly fictitious) point along this line. It will be marked invalid
	// if it is not situated between start and end point (but extrapolated).
	virtual Point2D getPointAt(double offsetFromStart) const override;
	// Get the point with the given number (index), result will be invalid for number < 0 or number >= this->getnumberOfPoints()
	Point2D getPoint(unsigned short number) const;
	// Returns the number of points this polyline is composed of (minimum: 2)
	unsigned short getNumberOfPoints() const;
	// Inserts the given point pt between point before-1 and point before. Returns false
	// and won't change if before < 0 or before > this->getNumberOfPoints().
	bool insertPoint(const Point2D& pt, unsigned short before);
	// Removes the point with given number (index). Will return false and won't change if
	// number < 0 or number >= this->getNumberOfPoints().
	bool removePoint(unsigned short number);
	// Returns the shortest Cartesian distance to the given point
	virtual double getDistance(const Point2D& point) const override;
	// Returns the shortest Cartesian distance to the other line
	virtual double getDistance(const Line2D& other) const override;
	// Translates this point according to the  given displacement
	virtual void moveBy(const Vector2D& displacement) override;
	// Translates this point according to the  given displacement
	virtual void moveBy(double deltaX, double deltaY) override;
	// Returns the length of his line
	virtual double getLength() const override;
	// Returns the bounding box of this line
	virtual BoundingBox2D getBounds() const override;
	// Draws the line on the Turtleizer canvas
	virtual void draw(Drawer2D& drawer) const override;
	// Checks whether there this is intersecting (or touching) the other line.
	virtual bool intersects(const Line2D& other) const override;
	// Returns true if some of the segments intersects another - this is not
	// the same as intersects(*this) - which would always be true!
	bool isSelfIntersecting() const;
	// string conversion operator for self-description
	virtual operator std::string() const override;
private:
	// Precision threshold for equality checks of angles among line segments
	static const double ANGLE_THRESHOLD;
	// We chose a deque because it allows relatively performant index access, insertion, and removal.
	typedef std::deque<Point2D> PointList;
	// List of intermediate points
	PointList detour;
	// Returns the nth segment (numer must be between 0 and getNumberOfPoints() - 2
	Line2D getSegment(unsigned short number) const;
};

#endif /*POLYLINE2D_H*/