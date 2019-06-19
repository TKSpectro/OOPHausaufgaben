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
#include "Polyline2D.h"
#include <cassert>
#include <limits>
#include <sstream>

const double Polyline2D::ANGLE_THRESHOLD = 1e-100;

Polyline2D::Polyline2D(const Point2D& p1, const Point2D& p2)
: Line2D(p1, p2)
{
}

Polyline2D::Polyline2D(const Point2D& p1, const Point2D& p2, unsigned int nInterPoints, Point2D interPoints[])
: Line2D(p1, p2)
{
	for (unsigned int ix = 0; ix < nInterPoints; ix++) {
		this->detour.push_back(interPoints[ix]);
	}
}

//Polyline2D::Polyline2D(const Polyline2D & other)
//	: Line2D(other)
//	, detour(other.detour)
//{
//}

Polyline2D::~Polyline2D()
{
	// Fortunately, the detour list deconstructs itself automatically,
	// so there isn't anything to be done explicitly, here.
}

Point2D Polyline2D::getPointAt(double offsetFromStart) const
{
	Point2D pt(0, 0, false);
	unsigned short i = 0;
	do {
		Line2D segment(this->getSegment(i));
		pt = segment.getPointAt(offsetFromStart);
		offsetFromStart -= segment.getLength();
		i++;
	} while (offsetFromStart > 0 && i <= this->detour.size());
	return pt;
}

Point2D Polyline2D::getPoint(unsigned short number) const
{
	if (number == 0) {
		return this->start;
	}
	else if (number == this->detour.size() + 1) {
		return this->end;
	}
	else if (number > 0 && number <= this->detour.size()) {
		return this->detour[number - 1];
	}
	return Point2D(0, 0, false);
}

unsigned short Polyline2D::getNumberOfPoints() const
{
	return this->detour.size() + 2;
}

bool Polyline2D::insertPoint(const Point2D& pt, unsigned short before)
{ 
	bool done = false;
	if (pt.isValid()) {
		if (before == 0) {
			// We have to replace (and shift) start point
			this->detour.push_front(this->start);
			this->start = pt;
			done = true;
		}
		else if (before == this->detour.size() + 2) {
			// We have to replace (and shift) end point
			this->detour.push_back(this->end);
			this->end = pt;
			done = true;
		}
		else if (before > 0 && before <= this->detour.size() + 1) {
			// Instead of specifying an index we can "compute" the appropriate iterator from begin by adding the index
			this->detour.insert(this->detour.begin() + (before - 1), pt);
			done = true;
		}
		// In any other case we refuse...
	}
	return done;
}

bool Polyline2D::removePoint(unsigned short number)
{
	bool done = false;
	if (number == 0) {
		// We have to replace (and drop) start point
		this->start = this->detour.front();
		this->detour.pop_front();
		done = true;
	}
	else if (number == this->detour.size() + 1) {
		// We have to replace (and drop) end point
		this->end = this->detour.back();
		this->detour.pop_back();
		done = true;
	}
	else if (number > 0 && number <= this->detour.size()) {
		// Instead of specifying an index we can "compute" the appropriate iterator from begin by adding the index
		this->detour.erase(this->detour.begin() + (number - 1));
		done = true;
	}
	// In any other case we refuse...
	return done;
}

double Polyline2D::getDistance(const Point2D& point) const
{
	double dist = std::numeric_limits<double>::infinity();
	for (unsigned short i = 0; i <= this->detour.size(); i++) {
		dist = min(dist, this->getSegment(i).getDistance(point));
	}
	return dist;
}

double Polyline2D::getDistance(const Line2D& other) const
{
	double dist = std::numeric_limits<double>::infinity();
	// Since the argument might also be subclassed, we must call the getDifference() method
	// on other line rather than on our segments, which are definitely of the base class!
	// (Thus we avoid the swapped subcall in the ancestor's method.)
	for (unsigned short i = 0; i <= this->detour.size(); i++) {
		dist = min(dist, other.getDistance(this->getSegment(i)));
	}
	return dist;
}

void Polyline2D::moveBy(const Vector2D& displacement)
{
	this->Line2D::moveBy(displacement);	// Moves start and end;
	for (PointList::iterator iter = this->detour.begin();
		iter != this->detour.end(); ++iter) {
		iter->moveBy(displacement);
	}
}

void Polyline2D::moveBy(double deltaX, double deltaY)
{
	this->moveBy(Vector2D(deltaX, deltaY));
}

void Polyline2D::draw(Drawer2D& drawer) const
{
	// If there ar no intermediate points then just delegate it to super
	if (this->detour.empty()) {
		this->Line2D::draw(drawer);
	}
	// If there are intermediate points then have each segment draw itself
	else {
		for (unsigned short i = 0; i <= this->detour.size(); i++) {
			this->getSegment(i).draw(drawer);
		}
	}
}

double Polyline2D::getLength() const
{
	double length = 0.0;
	const Point2D* prevPoint = &this->start;
	for (PointList::const_iterator iter = this->detour.begin();
		iter != this->detour.end(); ++iter) {
		length += prevPoint->getDistance(*iter);
		prevPoint = &*iter;
	}
	length += prevPoint->getDistance(this->end);
	return length;
}

BoundingBox2D Polyline2D::getBounds() const
{
	// As first approach we fetch the inherited bounds (including start and end)
	BoundingBox2D bounds = this->Line2D::getBounds();
	// Now we make sure that every intermediate point is contained, too
	for (PointList::const_iterator iter = this->detour.begin();
		iter != this->detour.end(); ++iter) {
		bounds.uniteWith(iter->getBounds());
	}
	return bounds;
}

bool Polyline2D::intersects(const Line2D& other) const
{
	// In order to check this we must be aware that the other line might be a plain
	// Line2D or a Polyline2D, which imposes different strategies. Fortunately, a
	// precaution in Line2D.intersects() will solve this problem for us:
	// - If other is a Line2D, then the parent method will decide immediately.
	// - If other is a Polyline2D then this method override will be called recursively
	//   with our segment now being the argument. So that other polyline will check
	//   segment for segment against our segment with the parent' method.
	bool inters = false;	// Unless we find an intersection, we assume it doesn't intersect
	unsigned short nPoints = this->getNumberOfPoints();
	for (unsigned short i = 0; !inters && i <= this->detour.size(); i++) {
		Line2D segm1(this->getSegment(i));
		inters = segm1.intersects(other);
	}
	return inters;
}

bool Polyline2D::isSelfIntersecting() const
{
	// Immediately neighbouring segments won't have to be checked for a crossing point
	// because they always share a point. But they should be checked for anti-parallelism
	// i.e. a segment might run back in the tracks of its predecessor - this can by checked
	// by comparing their vector angles (whether the reverse angle difference amongs to 0),
	// but this is an insecure test, due to limited precision. So we defined a class constant
	// ANGLE_THRESHOLD.

	// In order to check segments against each other for crossing we start picking the
	// first segment and check it against the third, fourth etc. (see preliminary comment
	// above), then we pick the second, check it against the fourth, fifth, and so on.
	// A backward check isn't necessary due to symmetry.
	// We might use either method intersects(...) or getDistance(...) == 0. We prefer
	// intersects() since it has way less overhead.
	// In addition we always check the immediate successor for anti-parallelism
	// Hence, the last segment to pick is the one starting at the (n-2)nd point where n
	// be the number of points. The (n-2)nd point has index n-3 (is below n-2).
	bool inters = false;	// Unless we find an intersection, we assume it doesn't intersect
	unsigned short nPoints = this->getNumberOfPoints();
	for (unsigned short i = 0; !inters && i < nPoints-2; i++) {
		Line2D segm1(this->getSegment(i));
		Vector2D vec2 = this->getSegment(i + 1).getVector();
		inters = abs(segm1.getVector().getOrientation() - vec2.scale(-1.0).getOrientation()) < ANGLE_THRESHOLD;
		for (unsigned short j = i + 2; !inters && j < nPoints - 1; j++) {
			inters = segm1.intersects(this->getSegment(j));
		}
	}
	return inters;
}

Line2D Polyline2D::getSegment(unsigned short number) const
{
	assert(number >= 0 && number <= this->detour.size());
	return Line2D(this->getPoint(number), this->getPoint(number + 1));
}

Polyline2D::operator std::string() const
{
	std::ostringstream str;
	str << "[" << this->start << " - (" << this->detour.size() << ") - " << this->end << "]";
	return str.str();
}