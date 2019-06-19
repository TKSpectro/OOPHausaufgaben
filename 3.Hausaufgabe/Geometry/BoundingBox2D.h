#pragma once
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
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

#include "Vector2D.h"

// Represents an enclosing rectangle around some shape. Internally, it will assume
// screen coordinates (i.e. bottom >= top). The methods getMinY() and getMaxY() will
// level the semantic difference, however, by returning what the name suggests.
class BoundingBox2D
{
public:
	BoundingBox2D(double left, double top, double right, double bottom);
	~BoundingBox2D();
	double getMinX() const;
	double getMaxX() const;
	double getMinY() const;
	double getMaxY() const;
	// Returns the extension in x direction
	double getSizeX() const;
	// Returns the extension in y direction
	double getSizeY() const;
	// Get diagonal vector (sensible?)
	Vector2D getDiagonal() const;
	// Expands to the area union of this and other (remark: It would have been way more
	// convenient if this method had returned a reference of me rather than void).
	void uniteWith(const BoundingBox2D& other);
private:
	double left, top;
	double right, bottom;
};

#endif /*BOUNDINGBOX_H*/