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
	Vehicle veh1;
	MotorVehicle veh2(60, 8E-5, MotorVehicle::PETROL);

	RoadNetwork rn;
	Point2D p1(50, 20);
	Junction j1(p1, rn, "Hanseplatz");
	TurtleDrawer2D drawer;
	Junction j2(Point2D(300, 250), rn, "Leipziger Platz");
	Polyline2D ls(p1, Point2D(200, 400));
	ls.insertPoint(Point2D(250, 100), 2);
	Road leipzigerStr(j1, j2, ls, "Leipziger Straﬂe");
	Road umweg(j2, j1, Polyline2D(Point2D(300, 250), Point2D(100, 150)), "Umweg");
	rn.draw(drawer);

	leipzigerStr.addVehicle(veh1, true);
	leipzigerStr.addVehicle(veh2, true);

	veh1.setSpeed(13.9);
	veh2.setSpeed(13.9);
	for (int i = 0; i < 100; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		rn.draw(drawer);
		cout << "veh1 is at position " << veh1.getPosition() << std::endl;
		cout << "veh2 is at position " << veh2.getPosition() << std::endl;
		if (i == 3) {
			veh2.setSpeed(13.9);
		}
	}

	return 0;
}