#pragma once
#ifndef TURTLEDRAWER2D_H
#define TURTLEDRAWER2D_H
/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * Zusatzaufgabe 8: Zeichnerklassenimplementation auf Basis Turtleizer.
 * Bibliotheksklasse, setzt Geometriebibliotheksprojekt (Teilaufgaben 1-7)
 * sowie Turtleizer-Bibliothek (https://github.com/codemanyak/Turtleizer_CPP)
 * voraus.
 *
 * Historie:
 * Datum		Beschreibung
 * ----------------------------------------------------------------------------
 * 24.05.2019	Erste Version
 */

#include "Drawer2D.h"

// This light-weight class implements the methods of the abstract class Drawer2D
// by means of the Turtleizer library (https://github.com/codemanyak/Turtleizer_CPP).
// If the coordinates passed to the drawing methods are meant to be geometrical
// coordinates then TurtleDrawer will draw anything upside down since it interprets
// them as screen coordinates with origin in the upper left corner. Moreover, there
// is no way to see anything drawn with negative coordinates.
// A more sophisticated subclass might offer a coordinate transformation (translation
// and scaling, mirroring included) via the constructor.
class TurtleDrawer2D : public Drawer2D
{
public:
	TurtleDrawer2D();
	virtual ~TurtleDrawer2D();
	// Draws a point with given style at coordinate pair (x, y).
	virtual void drawPoint(double x, double y,
		PointStyle style = PointStyle::PLAIN);
	// Draws a line from coordinate pair (x1,y1) to coordinate pair (x2,y2) with given width.
	// If dashLen > 0 then the line will be dashed with dash (and gap) length dashLen
	virtual void drawLine(double x1, double y1, double x2, double y2,
		unsigned short width = 1, unsigned short dashLen = 0);
private:
	// Counts the created instances (to detect when to wait for close).
	static unsigned long refCounter;
};

#endif /*TURTLEDRAWER2D_H*/