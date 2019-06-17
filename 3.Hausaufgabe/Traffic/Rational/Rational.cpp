#include "Rational.h"



Rational::Rational()
	: numerator(0LL)
	, denominator(1LL)
{
}

Rational::Rational(long long numerator, long long denominator)
	: numerator(numerator)
	, denominator(denominator)
{
	normalize();
}


Rational::~Rational()
{
}

Rational Rational::mul(Rational other)
{
	// Mathematisch völlig korrekt, aber numerisch fragwürdig.
	// Um unnötige Zahlenbereichsüberschreitungen zu vermeiden,
	// ist vorheriges Über-Kreuz-Kürzen sinnvoll
	//return Rational(numerator * other.numerator, denominator * other.denominator);
	long long div1 = gcd(numerator, other.denominator);
	long long div2 = gcd(other.numerator, denominator);
	return Rational((numerator/div1) * (other.numerator/div2), (denominator/div2) * (other.denominator/div1));
}

void Rational::normalize()
{
	long long divisor = gcd(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;
	if (denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}
}

long long Rational::gcd(long long a, long long b)
{
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	while (b != 0) {
		long long r = a % b;
		a = b;
		b = r;
	}
	return a == 0 ? 1 : a;
}
