#pragma once
class Rational
{
public:
	Rational();
	Rational(long long numerator, long long denominator = 1LL);
	~Rational();
	// Liefert das Produkt von this und other
	Rational mul(Rational other);
private:
	// Z�hler
	long long numerator;
	// Nenner
	long long denominator;
	// K�rzt Z�hler gegen Nenner und bringt ggf. das Vorzeichen in den Z�hler
	void normalize();
	// Berechnet den gr��ten gemeinsamen Teiler von a und b
	long long gcd(long long a, long long b);
};

