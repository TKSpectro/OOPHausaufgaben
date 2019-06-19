#include "Length.h"

const double Length::factors[] = { 0.3048, 0.9144, 1.0, 1000.0, 1609.3 };

Length::Length(double value, Unit unit)
	: val(value * factors[unit])
{
}

Length::~Length()
{
}

double Length::getValue(Unit unit)
{
	return this->val / factors[unit];
}
