#include"Line2D.h"
#include"Point2D.h"
#include"Vector2D.h"
#include"Polyline2D.h"
#include<iostream>



void outputPoint(Point2D point)
{
	cout << "x: " << point.getX() << " | y:" << point.getY() << endl;

	return;
}

void outputPoint(Point2D* point)
{
	cout << "x: " << point->getX() << " | y:" << point->getY() << endl;

	return;
}

void outputLine(Line2D line)
{
	cout << endl << "\tPoint1: ";
	outputPoint(line.getStart());
	cout << "\tPoint2: ";
	outputPoint(line.getEnd());
	cout << endl;
	return;
}

void outputVector(Vector2D vector)
{
	cout << "x: " << vector.getX() << " | y: " << vector.getY() << endl;
	return;
}

void outputBoundingBox(BoundingBox2D bound)
{
	cout << "StartPoint: ";
	outputPoint(bound.getStartPoint());
	cout << "\tWidth: " << bound.getWidth() << " Heigth: " << bound.getHeigth() << endl;
	return;
}


int main()
{
	Point2D p1(5, 6);
	double t = p1.getX();
	cout << t << endl;

	system("PAUSE");
	return 0;
}