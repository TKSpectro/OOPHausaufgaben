#pragma once
#ifndef DRAWER2D_H
#define DRAWER2D_H
/*
 * Fachhochschule Erfurt www.fh-erfurt.de/ai
 * Fachgebiet Angewandte Informatik
 * Modul Objektorientierte Programmierung
 *
 * Musterlösung zur Hausaufgabe 01
 * Thema: Geometrische Basisklassen
 * Autor: Kay Gürtzig
 *
 * Zusatzaufgabe 7: Abstrakte Zeichnerklasse
 *
 * Historie:
 * Datum		Beschreibung
 * ----------------------------------------------------------------------------
 * 23.05.2019	Erste Version
 */

// This Vector2D class may facilitate the implementation of Drawer2D subclasses.
#include "Vector2D.h"

// Abstract class providing the interface for drawing geometrical primitives on some canvas
class Drawer2D
{
public:
	enum PointStyle {PLAIN, SQUARE, RHOMBOID, CROSS, PLUS};
	virtual ~Drawer2D();
	// Draws a point with given style at coordinate pair (x, y).
	virtual void drawPoint(double x, double y,
		PointStyle style = PointStyle::PLAIN) = 0;
	// Draws a line from coordinate pair (x1,y1) to coordinate pair (x2,y2) with given width.
	// If dashLen > 0 then the line will be dashed with dash (and gap) length dashLen
	virtual void drawLine(double x1, double y1, double x2, double y2,
		unsigned short width = 1, unsigned short dashLen = 0) = 0;
};

#endif /*DRAWER2D_H*/