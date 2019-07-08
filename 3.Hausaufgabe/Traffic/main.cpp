#include "Vehicle.h"
#include "RoadNetwork.h"
#include "MotorVehicle.h"
#include "Length.h"
#include "Junction.h"
#include "Road.h"
#include "TurtleDrawer2D.h"
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::endl;

int main()
{
	TurtleDrawer2D drawer;
	
	RoadNetwork rn;
	Point2D p1(100, 120);
	Junction j1(p1, rn, "Hanseplatz");
	Junction j2(Point2D(300, 250), rn, "Leipziger Platz");
	Polyline2D ls(p1, Point2D(200, 400));
	ls.insertPoint(Point2D(250, 100), 2);
	Road leipzigerStr(j1, j2, ls, "Leipziger Straﬂe");
	Road umweg(j2, j1, Polyline2D(Point2D(300, 250), Point2D(100, 150)), "Umweg");

	// Test the ouput of an existing roadnetwork
	//rn.save("output.txt");

	// Test the input of an roadnetwork via a text file
	RoadNetwork rn2;
	rn2.load("input.txt");

	//Output rn2
	rn2.save("outputRN2.txt");

	rn2.draw(drawer);

	//system("pause");
	return 0;
}