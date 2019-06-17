#include "MotorVehicle.h"

#include <cmath>

MotorVehicle::MotorVehicle(double maxEnergyReserves, double consumption, EnergySourceType energySource)
	: capacity(maxEnergyReserves)
	, consumption(consumption)
	, energyType(energySource)
	, startReserves(0.0)
{
}


MotorVehicle::~MotorVehicle()
{
}

double MotorVehicle::getPosition(Length::Unit unit) const
{
	double pos = this->Vehicle::getPosition();
	double reach = this->getReachablePosition();
	if (pos >= this->startPosition && pos > reach || pos < this->startPosition && pos < reach) {
		pos = reach;
	}
	return Length(pos).getValue(unit);
}

double MotorVehicle::getSpeed() const
{
	double velocity = 0.0;
	double pos = this->Vehicle::getPosition();
	double reach = this->getReachablePosition();
	if (pos >= this->startPosition && pos <= reach || pos < this->startPosition && pos >= reach) {
		velocity = Vehicle::getSpeed();
	}
	return velocity;
}

double MotorVehicle::getEnergyReserves() const
{
	double distance = abs(this->getPosition() - this->startPosition);
	return this->startReserves - this->consumption * distance;
}

double MotorVehicle::refillReserves(double amount)
{
	double added = 0;
	if (amount >= 0) {
		setSpeed(0);
		double hole = this->capacity - this->startReserves;
		if (amount == 0 || amount > hole) {
			added = hole;
		}
		else {
			added = amount;
		}
		this->startReserves += added;
	}
	return added;
}

void MotorVehicle::setSpeed(double newSpeed)
{
	double reserves = this->getEnergyReserves();
	this->Vehicle::setSpeed(newSpeed);
	this->startReserves = reserves;
}

double MotorVehicle::getReachablePosition() const
{
	double radius = this->startReserves / this->consumption;
	double speed = this->Vehicle::getSpeed();
	return this->startPosition + (speed < 0 ? -1 : 1) * radius;
}
