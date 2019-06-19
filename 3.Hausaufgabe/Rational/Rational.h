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
	// Zähler
	long long numerator;
	// Nenner
	long long denominator;
	// Kürzt Zähler gegen Nenner und bringt ggf. das Vorzeichen in den Zähler
	void normalize();
	// Berechnet den größten gemeinsamen Teiler von a und b
	long long gcd(long long a, long long b);
};

