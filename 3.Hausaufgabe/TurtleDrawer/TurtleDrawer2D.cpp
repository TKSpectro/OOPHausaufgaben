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
#define _USE_MATH_DEFINES

#include "TurtleDrawer2D.h"
#include "Turtleizer.h"
#include <cmath>

unsigned long TurtleDrawer2D::refCounter = 0;

TurtleDrawer2D::TurtleDrawer2D()
{
	refCounter++;
	hideTurtle();
}


TurtleDrawer2D::~TurtleDrawer2D()
{
	if (--refCounter <= 0) {
		Turtleizer::awaitClose();
	}
}

// Draws a point with given style at coordinate pair (x, y).
void TurtleDrawer2D::drawPoint(double x, double y, PointStyle style)
{
	double angle = getOrientation();
	gotoXY(x, y);
	// Turn North
	left(angle);
	penDown();
	switch (style) {
	case PointStyle::PLAIN:
	case PointStyle::RHOMBOID:
		penUp();
		forward(1);
		penDown();
		right(45);
		for (int i = 1; i <= 4; i++) {
			right(90);
			forward(sqrt(M_SQRT2));
		}
		// Turn back North
		left(45);
		break;
	case PointStyle::SQUARE:
		penUp();
		forward(1);
		right(90);
		backward(1);
		penDown();
		for (int i = 1; i <= 4; i++) {
			forward(2);
			right(90);
		}
		// Turn back North
		left(90);
		break;
	case PointStyle::CROSS:
		right(45);
		for (int i = 1; i <= 4; i++) {
			forward(M_SQRT2);
			backward(M_SQRT2);
			right(90);
		}
		// Turn back North
		left(45);
		break;
	case PointStyle::PLUS:
		for (int i = 1; i <= 4; i++) {
			forward(2);
			backward(2);
			right(90);
		}
		break;
	default:
		forward(1);
	}
	// Turn back to original orientation
	right(angle);
}

// Draws a line from coordinate pair (x1,y1) to coordinate pair (x2,y2) with given width.
// If dashLen > 0 then the line will be dashed with dash (and gap) length dashLen
void TurtleDrawer2D::drawLine(double x1, double y1, double x2, double y2,
	unsigned short width, unsigned short dashLen)
{
	double oldAngle = getOrientation();	// Old turtle orientation in degrees from North
	gotoXY(x1, y1);
	// turn right
	right(90 - oldAngle);
	Vector2D vec(x2 - x1, y2 - y1);
	double length = vec.getLength();
	double angle = vec.getOrientation() * 180.0 / M_PI;
	right(angle);
	penDown();
	if (dashLen == 0) {
		forward(vec.getLength());
	}
	else {
		bool down = true;
		while (length > 0) {
			forward(dashLen);
			length -= dashLen;
			if (down && length > dashLen) {
				penUp();
			}
			else {
				penDown();
			}
			down = !down;
		}
	}
}
