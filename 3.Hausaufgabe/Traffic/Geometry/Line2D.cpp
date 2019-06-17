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
 * 24.05.2019	Vererbungsproblem mit Methode intersects gelöst.
 */
#include "Line2D.h"
#define _USE_MATH_DEFINES 
#include <cmath>
#include <limits>
#include <sstream>
#include <typeinfo>

Line2D::Line2D(const Point2D& p1, const Point2D& p2)
: start(p1)
, end(p2)
{
}

Line2D::~Line2D()
{
}

// Returns (a copy of) the starting point of this line stretch
Point2D Line2D::getStart() const
{
	return this->start;
}

// Returns (a copy of) the ending point of this line stretch
Point2D Line2D::getEnd() const
{
	return this->end;
}

// Returns a (possibly fictitious) point along this line. It will be marked invalid
// if it is not situated between start and end point (but extrapolated).
Point2D Line2D::getPointAt(double offsetFromStart) const
{
	double length = this->getLength();
	Point2D point = this->start.add(this->getVector().scale(offsetFromStart / length));
	if (offsetFromStart < 0 || offsetFromStart > this->getLength()) {
		// Make an invalid copy from it
		point = Point2D(point.getX(), point.getY(), false);
	}
	return point;
}


// Returns the shortest Cartesian distance to the given point
double Line2D::getDistance(const Point2D& point) const
{
	double dist = 0.0;
	// First we construct the orthogonal projection from point onto this line
	Vector2D myVec = this->getVector();
	Vector2D orthVec(-myVec.getY(), myVec.getX());
	Point2D projPt = this->getCrosspoint(Line2D(point, point.add(orthVec)));
	// ... if the projection point lies between start and end then we have the distance
	if (projPt.isValid() && this->contains(projPt)) {
		dist = point.getDistance(projPt);
	}
	// ... otherwise it will be the shorter distance from either start or end
	else {
		dist = min(this->start.getDistance(point), this->end.getDistance(point));
	}
	return dist;
}

// Returns the shortest Cartesian distance to the other line
double Line2D::getDistance(const Line2D& other) const
{
	// Care for potential polymorphism of other but avoid cyclic recursion
	if (typeid(other) != typeid(Line2D) && typeid(*this) == typeid(Line2D)) {
		return other.getDistance(*this);
	}
	double dist = std::numeric_limits<double>::infinity();
	Point2D crossing = getCrosspoint(other);
	// If a cross point exists between my points then the distance is zero
	bool contains1 = crossing.isValid() && this->contains(crossing);
	bool contains2 = crossing.isValid() && other.contains(crossing);
	if (contains1 && contains2) {
		dist = 0.0;
	}
	else if (contains1) {
		dist = other.getDistance(crossing);
	}
	else if (contains2) {
		dist = this->getDistance(crossing);
	}
	dist = min(dist, this->getDistance(other.getStart()));
	dist = min(dist, this->getDistance(other.getEnd()));
	dist = min(dist, other.getDistance(this->getStart()));
	dist = min(dist, other.getDistance(this->getEnd()));
	return dist;
}

// Returns a vector from start to end point
Vector2D Line2D::getVector() const
{
	return this->end.getDifference(this->start);
}

// returns the length of his line
double Line2D::getLength() const
{
	return this->start.getDistance(this->end);
}


// Translates this point according to the  given displacement
void Line2D::moveBy(const Vector2D& displacement)
{
	this->start.moveBy(displacement);
	this->end.moveBy(displacement);
}

// Translates this point according to the  given displacement
void Line2D::moveBy(double deltaX, double deltaY)
{
	this->start.moveBy(deltaX, deltaY);
	this->end.moveBy(deltaX, deltaY);
}

// Returns the bounding box of this line
BoundingBox2D Line2D::getBounds() const
{
	// If uniteWith had returned a reference of the BountgBox2D object then it might have been as elegan as this:
	//return this->start.getBounds().uniteWith(this->end.getBounds());
	BoundingBox2D bounds = this->start.getBounds();
	bounds.uniteWith(this->end.getBounds());
	return bounds;
}

// draws the line by means of drawer object
void Line2D::draw(Drawer2D& drawer) const
{
	drawer.drawLine(this->start.getX(), this->start.getY(), this->end.getX(), this->end.getY());
}

// Returns true if point is situated on this line between start and end point
// To make sense it is required that point is located on the (prolongated) line!
bool Line2D::contains(const Point2D& point) const
{
	BoundingBox2D bounds = this->getBounds();
	return bounds.getMinX() <= point.getX() && point.getX() <= bounds.getMaxX()
		&& bounds.getMinY() <= point.getY() && point.getY() <= bounds.getMaxY();
}

// Constructs the virtual crosspoint with other line. The point may be outside the stretches of
// either line and will only be marked invalid if it doesn't exist or isn't unique. Consider
// checking with one of the methods contains or intersects.
Point2D Line2D::getCrosspoint(const Line2D& other) const
{
	// We do a very detailed case analysis to tackle as many as possible challenges
	// Some invalid results might have been achieved easier (simple by letting overflow
	// or didiviion by zero happen) but to squeeze valid results in cases where they
	// are achievable, some preparatory analysis is never wrong.
	const double infinity = std::numeric_limits<double>::infinity();
	Point2D crossPoint(infinity, infinity);
	// We have to solve the equation system (two coordinate equations) for some s, t:
	// this->start + s * (this->end - this.start) == other.start + t * (other.end - other.start)
	Vector2D thisVec = this->getVector();
	Vector2D otherVec = other.getVector();
	// this->start.x + s * thisVec.x = other.start.x + t * otherVec.x | e.g. / thisVec.x
	// this->start.y + s * thisVec.y = other.start.y + t * otherVec.y | e.g. / thisVec.y
	// (this->start.x - other.start.x)/ thisVec.x - (this->start.y - other.start.y) / thisVec.y = t * (otherVec.x/thisVec.x - otherVec.y/thisVec.y)
	if (thisVec.getX() != 0 && thisVec.getY() != 0) {
		// Solve for t
		double t =
			((this->start.getX() - other.start.getX()) / thisVec.getX()
			- (this->start.getY() - other.start.getY()) / thisVec.getY()) /
			// The difference in the following denominator might still compute
			// to zero (indicating parallels), in which case an invalid result
			// is quite okay, however.
			(otherVec.getX() / thisVec.getX() - otherVec.getY() / thisVec.getY());
		crossPoint = other.start.add(otherVec.scale(t));
	}
	else if (otherVec.getX() != 0 && otherVec.getY() != 0) {
		// Solve for s
		double s =
			((other.start.getX() - this->start.getX()) / otherVec.getX()
			- (other.start.getY() - this->start.getY()) / otherVec.getY()) /
			// The difference in the following denominator might still compute
			// to zero (indicating parallels), in which case an invalid result
			// is quite okay, however.
			(thisVec.getX() / otherVec.getX() - thisVec.getY() / otherVec.getY());
		crossPoint = this->start.add(thisVec.scale(s));
	}
	// Special treatment for vertical or horizontal lines
	else if (thisVec.getX() == 0) {
		// this line is vertical (no diff in x)
		if (otherVec.getY() == 0) {
			// other line is horizontal -> simple
			crossPoint = Point2D(this->start.getX(), other.start.getY());
		}
		else if (otherVec.getX() != 0) {
			// other is neither horizontal nor vertical -> crosspoint exists, find it by scaling other's vector
			crossPoint = Point2D(this->start.getX(), other.start.getY() + ((this->start.getX() - other.start.getX()) / otherVec.getX() * otherVec.getY()));
		}
		else if (this->start.getX() == other.start.getX()) {
			// both lines vertical and sharing x coordinate -> not valid but with definite x coordinate
			crossPoint = Point2D(this->start.getX(), infinity);
		}
		// Both lines vertical but not at same x coordinate -> no valid solution
	}
	else if (thisVec.getY() == 0) {
		// this line is horizontal (no diff in y)
		if (otherVec.getX() == 0) {
			// other line is vertical -> simple
			crossPoint = Point2D(other.start.getX(), this->start.getY());
		}
		else if (otherVec.getY() != 0) {
			// other ist neither vertical nor horizontal -> crosspoint exists, find it by scaling other's vector
			crossPoint = Point2D(other.start.getX() + ((this->start.getY() - other.start.getY()) / otherVec.getY() * otherVec.getX()), this->start.getY());
		}
		else if (this->start.getY() == other.start.getY()) {
			// both lines horizontal but sharing y coordinate -> not valid but with definite y coordinate
			crossPoint = Point2D(infinity, this->start.getY());
		}
	}
	else if (otherVec.getY() == 0) {
		// this line neither horizontal nor vertical but other line horizontal (no diff in y)
		crossPoint = Point2D(this->start.getX() + ((other.start.getY() - this->start.getY()) / thisVec.getY() * otherVec.getX()), other.start.getY());
	}
	else if (otherVec.getX() == 0) {
		// this line neither horizontal nor vertical but other line vertical (no diff in x)
		crossPoint = Point2D(other.start.getX(), this->start.getY() + ((other.start.getX() - this->start.getX()) / thisVec.getX() * thisVec.getY()));
	}
	// All other cases (are there any?) will remain with an invalid point
	return crossPoint;
}

// Simply checks intersection (crossing within bounds)
bool Line2D::intersects(const Line2D& other) const
{
	// NOTE: This method is a nice example for inheritance problems: If a Polyline2D
	// (or some other still unknown subclass object) happens to be passed as an argument
	// then we get into deep trouble here - this class doesn't know about its offsprings
	// and cannot handle it therefore. So the only thing we can do is check whether the
	// argument is not a basic Line2D - in this case we might have the subclass line do
	// the job if it is more clever. But we must avoid eternal thrashing recursion here
	//- so we better make sure that this line is a plain Line2D.
	if (typeid(other) != typeid(Line2D) && typeid(*this) == typeid(Line2D)) {
		return other.intersects(*this);
	}
	Point2D crossing = this->getCrosspoint(other);
	return crossing.isValid() && this->contains(crossing) && other.contains(crossing);
}

double Line2D::min(double a, double b)
{
	return (a < b) ? a : b;
}

Line2D::operator std::string() const
{
	std::ostringstream str;
	str << "[" << this->start << " - " << this->end << "]";
	return str.str();
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& str, const Line2D& line)
{
	str << string(line);
	return str;
}