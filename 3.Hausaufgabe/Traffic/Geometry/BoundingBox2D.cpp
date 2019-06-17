/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * Einhüllendes Rechteck im zweidimensionalen reellen Raum (Zeichenebene)
 *
 * Historie:
 * Datum		Beschreibung
 * 23.05.2019	Erste Version
 */
#include "BoundingBox2D.h"
#include <minmax.h>

BoundingBox2D::BoundingBox2D(double left, double top, double right, double bottom)
: left(min(left, right))
, top(min(bottom, top))
, right(max(left,right))
, bottom(max(top,bottom))
{
}


BoundingBox2D::~BoundingBox2D()
{
}

double BoundingBox2D::getMinX() const
{
	return this->left;
}

double BoundingBox2D::getMaxX() const
{
	return this->right;
}

double BoundingBox2D::getMinY() const
{
	return this->top;
}

double BoundingBox2D::getMaxY() const
{
	return this->bottom;
}

double BoundingBox2D::getSizeX() const
{
	return this->right - this->left;
}
double BoundingBox2D::getSizeY() const
{
	return this->bottom - this->top;
}
Vector2D BoundingBox2D::getDiagonal() const
{
	return Vector2D(this->getSizeX(), this->getSizeY());
}

// expands to the area union of this and other
void BoundingBox2D::uniteWith(const BoundingBox2D& other)
{
	if (other.left < this->left)     this->left = other.left;
	if (other.right > this->right)   this->right = other.right;
	if (other.top < this->top)       this->top = other.top;
	if (other.bottom > this->bottom) this->bottom = other.bottom;
}
