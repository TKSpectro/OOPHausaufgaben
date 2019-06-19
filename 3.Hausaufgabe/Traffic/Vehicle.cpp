#include "Vehicle.h"
#include "Road.h"
#include "Point2D.h"

Vehicle::Vehicle()
	: speed(0.0)
	, startPosition(0.0)
	, startTime(time(nullptr))
{
}


Vehicle::~Vehicle()
{
}

double Vehicle::getPosition(Length::Unit unit) const
{
	return Length(startPosition + speed * difftime(time(nullptr), startTime)).getValue(unit);
}

double Vehicle::getSpeed() const
{
	return this->speed;
}

void Vehicle::setSpeed(double newSpeed)
{
	this->startPosition = this->getPosition();
	this->speed = newSpeed;
	this->startTime = time(nullptr);
}

void Vehicle::draw(Drawer2D & drawer) const
{
	if (this->road != nullptr) {
		Point2D coords = this->road->getPosition(*this);
		if (coords.isValid()) {
			drawer.drawPoint(coords.getX(), coords.getY());
		}
	}
}
