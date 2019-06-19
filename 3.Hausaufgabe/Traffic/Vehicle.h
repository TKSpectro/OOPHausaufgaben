#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include <ctime>
#include "Length.h"
#include "Drawer2D.h"

class Road;

class Vehicle
{
public:
	Vehicle();
	~Vehicle();
	// Returns the current position along the virtual way in the given length unit
	virtual double getPosition(Length::Unit unit = Length::METRE) const;
	// Returns the current velocity in meters per second
	virtual double getSpeed() const;
	// Changes the velocity to the given speed (in metres per second)
	virtual void setSpeed(double newSpeed);
	// Draws the vehicle at its current geographic position
	virtual void draw(Drawer2D& drawer) const;
protected:
	// Start position of the current motion phase
	double startPosition;
private:
	friend class Road;
	// Current velocity in metres per second
	double speed;
	// Start time of the current motion phase
	time_t startTime;
	// Pointer to the road this vehicle is on
	Road* road;
};

#endif /*VEHICLE_H*/