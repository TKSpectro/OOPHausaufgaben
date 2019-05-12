#include "Polyline2D.h"
#include "Point2D.h"
#include<iterator>

Polyline2D::Polyline2D(const Point2D& StartPoint, const Point2D& EndPoint)
{

	it = this->Points.begin();
	this->Points[*it] = StartPoint;
	it = this->Points.end() - 1;
	this->Points[*it] = EndPoint;

}
Polyline2D::~Polyline2D()
{
}

double Polyline2D::getLength() const
{
	double sum = 0.0;
	for (it = this->Points.begin(); it != this->Points.end(); it++)
	{
		Line2D line(this->Points[*it], this->Points[*it + 1]);
		sum += line.getLength();
	}
	return sum;
}

bool Polyline2D::isLine2D()
{

	if (this->Points.size() == 2)
		return true;
	else
		return false;
}

Point2D Polyline2D::getPoint(unsigned short number) const
{
	if (number > this->Points.size())
	{
		//hier muss isValide umgesetzt werden, samit wir eine ungültige Punkt bekommen
	}
	else
	{
		it = this->Points.begin();
	advance: (it, number);
		return Point2D(this->Points[*it]);
	}
}

unsigned short Polyline2D::getNumberOfPoints() const
{

	return Points.size();
}

bool Polyline2D::insertPoint(const Point2D & pt, unsigned short before)
{ //muss fragen was er mit Before meinte, ob die Stelle nach before oder vor Before . 
	if (Points.size() == 0)
		return false;

	else
	{
		advance(it, before);
		it--;
		Points.insert(it, pt);
	}
	return true;
}

bool Polyline2D::removePoint(unsigned short number)
{
	if (Points.size() == 0)
		return false;
	else
	{
		advance(it, number);
		Points.erase(it);
	}
	return true;
}

bool Polyline2D::isSelfIntersecting() const
{ //TODO keine Ahnung was er will..... Fragen
	return false;
}
