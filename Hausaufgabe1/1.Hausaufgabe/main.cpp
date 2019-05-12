#include"Line2D.h"
#include"Point2D.h"
#include"Vector2D.h"

#include<iostream>

using namespace std;

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
	cout << "\tWidth: " << bound.getWidth() << " Height: " << bound.getHeight() << endl;
	return;
}

void vectorTest()
{
	cout << "| Start VectorTest |" << endl;

	Vector2D vector1(4, 6);
	Vector2D vector2(1, 1);

	cout << "getX() Test: " << vector1.getX() << endl;

	cout << "getY() Test: " << vector1.getY() << endl;

	cout << "add(vector) Test: ";
	outputVector(vector1.add(vector2));

	cout << "substract() Test: ";
	outputVector(vector1.subtract(vector2));

	cout << "getLength() Test: " << vector1.getLength() << endl;

	cout << "getOrientation() Test: " << vector1.getOrientation() << endl;

	cout << "multiply() Test: " << vector1.multiply(vector2) << endl;

	cout << "| End VectorTest |" << endl;
	return;
}

void pointTest()
{
	cout << "| Start PointTest |" << endl;
	Point2D point0(5, 2);
	Point2D point1(0, 1);
	Point2D point2(20, 21);
	Vector2D vector1(4, 6);
	Vector2D vector2(1, 1);

	cout << "getX() Test: " << point0.getX() << endl;

	cout << "getY() Test: " << point0.getY() << endl;

	cout << "isValid() Test: " << point0.isValid() << endl;

	cout << "add(vector) Test: ";
	outputPoint(point0.add(vector1));

	cout << "getDifference(point) Test: ";
	outputVector(point0.getDifference(point1));

	cout << "getDistance() Test: " << point0.getDistance() << endl;

	cout << "getDistance(point) Test: " << point0.getDistance(point1) << endl;

	cout << "moveBy(vector) Test: ";
	point0.moveBy(vector2);
	outputPoint(point0);

	cout << "moveBy(x, y) Test: ";
	point0.moveBy(1, 1);
	outputPoint(point0);

	cout << "moveTo() Test: ";
	point0.moveTo(5, 2);
	outputPoint(point0);

	cout << "getBounds() Test: ";
	outputBoundingBox(point0.getBounds());

	cout << "| End VectorTest |";
	return;
}

void lineTest()
{
	cout << "| Start LineTest |" << endl;

	Line2D line1(Point2D(1, 2), Point2D(6, 3));
	Line2D line2(Point2D(2, 2), Point2D(6, 2));
	Line2D line3(Point2D(2, 0), Point2D(4, 0));
	Line2D line4(Point2D(6, 2), Point2D(8, 2));
	Vector2D vector1(1, 1);
	Point2D point1(7, 4);
	
	cout << "getStart() Test: ";
	outputPoint(line1.getStart());

	cout << "getEnd() Test: ";
	outputPoint(line1.getEnd());

	cout << "getPointAt(offset) Test: ";
	outputPoint(line1.getPointAt(4));

	cout << "getLength() Test: " << line1.getLength() << endl;

	Line2D line5 = line1.add(vector1);
	cout << "add(vector) Test: ";
	outputLine(line5);

	cout << "getVector() Test: ";
	outputVector(line1.getVector());

	cout << "moveBy(vector) Test: ";
	line1.moveBy(vector1);
	outputLine(line1);

	cout << "moveBy(x,y) Test: ";
	line1.moveBy(-1, -1);
	outputLine(line1);

	cout << "isParallel(line) Test: Line1,Line2 : " << line1.isParallel(line2) << endl; 
	cout << "isParallel(line) Test: Line3,Line4 : " << line3.isParallel(line4) << endl;

	cout << "getDistance(point) Test: " << line1.getDistance(point1) << endl;

	cout << "getDistance(line) Test: Line1,Line2 " << line1.getDistance(line2) << endl;
	cout << "getDistance(line) Test:Line3,Line4 " << line3.getDistance(line4) << endl;

	cout << "getBounds() Test: ";
	BoundingBox2D box1 = line1.getBounds();
	outputBoundingBox(box1);

	cout << "| End LineTest |";
	return;
}

//void BoundingBoxTest()
//{
//	BoundingBox2D box(Point2D(0,0),4, 2);
//	cout << "getWidth() Test: " << box.getWidth() << endl;
//
//	cout << "getHeight() Test: " << box.getHeight() << endl;
//
//	cout << "getStartPoint() Test: ";
//	outputPoint(box.getStartPoint());
//		
//	return;
//}

int main()
{

	lineTest();				//abgeschlossen
	//vectorTest();			//abgeschlossen
	//pointTest();			//abgeschlossen
	//BoundingBoxTest();

	system("PAUSE");
	return 0;
}