#include "Rational.h"

int main()
{
	Rational bruch;
	Rational bruch1(3, -7);
	Rational bruch2(5);

	Rational bruch3 = bruch1.mul(Rational(5, 9));

	return 0;
}