#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H
/*
* Fachhochschule Erfurt www.fh-erfurt.de/ai
* Fachgebiet Angewandte Informatik
* Modul Objektorientierte Programmierung
*
* Musterlösung zur Hausaufgabe 01
* Thema: Geometrische Basisklassen
* Autor: Kay Gürtzig
*
* Nicht ortsfester Vektor im zweidimensionalen reellen Raum (Zeichenebene)
*
* Historie:
* Datum		Beschreibung
* 23.05.2029	Erste Version
*/
#include <string>
#include <ostream>

// Class represents (a non-located) two-dimensional geometrical vector
class Vector2D
{
public:
	// Creates a new vector either from Cartesian or polar coordinates, according to asCoordDiffs
	Vector2D(double xDiffOrLength = 0.0, double yDiffOrAngle = 0.0, bool asCoordDiffs = true);
	~Vector2D();
	// Returns the X length
	double getX() const;
	// Returns the Y length
	double getY() const;
	// Returns the length of the vector
	double getLength() const;
	// Returns the angle as mathematic orientation in radians
	double getOrientation() const;
	// Returns the vectorial sum of this vector and other
	Vector2D add(const Vector2D& other) const;
	// Returns the vectorial difference among this vector and other
	Vector2D subtract(const Vector2D& other) const;
	// Returns a sclaed vector with saclar factor
	Vector2D scale(double factor) const;
	// Returns the scalar product of this vector and other
	double multiply(const Vector2D& other) const;
	// string conversion operator for self-description
	operator std::string() const;
private:
	// Extension in x direction
	double deltaX;
	// extension in y direction
	double deltaY;
};

// stream output operator to facilitate debugging
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& str, const Vector2D& vec);

#endif /*VECTOR2D_H*/