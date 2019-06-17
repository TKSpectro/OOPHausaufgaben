#include "Length.h"

const double Length::Factor[] = { 1.0, 0.001 , 0.01 };

Length::Length(double val, Unit unit)
	:value(val*Factor[unit])
{

}
Length::~Length()
{
}

double Length::getValue(Unit unit)
{
	return value / Factor[unit];
}