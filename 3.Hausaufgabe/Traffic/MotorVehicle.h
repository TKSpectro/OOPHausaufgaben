#pragma once
#include "Vehicle.h"
class MotorVehicle :
	public Vehicle
{
public:
	enum EnergySourceType {PETROL, DIESEL, LPG, HYDROGEN, ELECTRO};
	MotorVehicle(double maxEnergyReserves, double consumption, EnergySourceType energySource = ELECTRO);
	~MotorVehicle();
	// Returns the current position along the virtual way in the given length unit
	virtual double getPosition(Length::Unit unit = Length::METRE) const;
	// Returns the current velocity in meters per second
	virtual double getSpeed() const override;
	// Returns the current amount of energy reserves
	double getEnergyReserves() const;
	// Feeds new energy reserves (as much as possible up to the given amount,
	// regarding capacity, 0 = fill up), returns actually loaded amount
	double refillReserves(double amount = 0);
	// Changes the velocity to the given speed (in metres per second)
	virtual void setSpeed(double newSpeed);
private:
	const EnergySourceType energyType;
	// Maximum amount of energy reserves in energy units
	const double capacity;
	// Nominal consumption in energy unit per metre
	const double consumption;
	// Energy reserves at the beginnng of the current motion phase
	double startReserves;
	// Returns the extreme position reachable with the start energy reserves in speed direction
	double getReachablePosition() const;
};

