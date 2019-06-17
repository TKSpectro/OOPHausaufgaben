#pragma once
#ifndef LENGTH_H
#define LENGTH_H

class Length
{
public:
	enum Unit {FOOT, YARD, METRE, KILOMETRE, MILE};
	Length(double value = 0.0, Unit unit = METRE);
	~Length();
	// Returns the length value in the given unit
	double getValue(Unit unit = METRE);
private:
	// Conversion factors from METRE to the respective length unit
	static const double factors[];
	// Length value in METREs
	double val;
};

#endif /*LENGTH_H*/