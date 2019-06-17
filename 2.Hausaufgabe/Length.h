#pragma once
class Length

{
public:
	enum Unit { METRE, MILLIMETRE, CENTIMETRE};

	Length(double Val = 0.0, Unit unit= METRE);
	~Length();

	// returns the value in the given unit
	double getValue(Unit unit = METRE);

private:
	static const double Factor[];
	double value;
};

