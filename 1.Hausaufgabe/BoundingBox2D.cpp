#include"BoundingBox2D.h"
#include"Point2D.h"

BoundingBox2D::BoundingBox2D()
	:StartPoint(&Point2D(0, 0)), Width(0), Heigth(0)
{
}

BoundingBox2D::BoundingBox2D(Point2D& start, double width, double heigth)
	: StartPoint(&start), Width(width), Heigth(heigth)
{
}

BoundingBox2D::~BoundingBox2D()
{
}

double BoundingBox2D::getWidth() const
{
	return this->Width;
}

double BoundingBox2D::getHeigth() const
{
	return this->Heigth;
}

Point2D BoundingBox2D::getStartPoint() const
{
	Point2D p1(StartPoint->getX(),StartPoint->getY());
	return p1;
}
void BoundingBox2D::uniteWith(const BoundingBox2D &other)
{
	double newX = this->StartPoint->getX();
	double newY = this->StartPoint->getY();
	double newWidth = 0.0;
	double newHeigth = 0.0;

	//New StartPoint
	if(other.StartPoint->getX() < newX)
		newX = other.StartPoint->getX();
	if(other.StartPoint->getY() < newY)
		newY = other.StartPoint->getY();
	Point2D newStartPoint(newX, newY);

	//Create all corner points
	Point2D ulCorner1(this->StartPoint->getX(), this->StartPoint->getY() + Heigth);
	Point2D lrCorner1(this->StartPoint->getX() + Width, this->StartPoint->getY());
	Point2D ulCorner2(other.StartPoint->getX(), other.StartPoint->getY() + Heigth);
	Point2D lrCorner2(other.StartPoint->getX() + Width, other.StartPoint->getY());

	//New Heigth
	double newHeigthX = 0.0;
	double newHeigthY = 0.0;
	if(ulCorner1.getX() < ulCorner2.getX())
		newHeigthX = ulCorner1.getX();
	else
		newHeigthX = ulCorner2.getX();
	if(ulCorner1.getY() < ulCorner2.getY())
		newHeigthY = ulCorner1.getY();
	else
		newHeigthY = ulCorner2.getY();
	Point2D newULCorner(newHeigthX, newHeigthY);

	this->Heigth = newStartPoint.getDistance(newULCorner);

	//New Width
	double newWidthX = 0.0;
	double newWidthY = 0.0;
	if(lrCorner1.getX() < lrCorner2.getX())
		newWidthX = lrCorner1.getX();
	else
		newWidthX = lrCorner2.getX();
	if(lrCorner1.getY() < lrCorner2.getY())
		newWidthY = lrCorner1.getY();
	else
		newWidthY = lrCorner2.getY();
	Point2D newLRCorner(newWidthY, newWidthX);

	this->Width = newStartPoint.getDistance(newLRCorner);
}

void BoundingBox2D ::draw(Drawer2D& drawer) const
{
	drawer.DrawBoundingBox(StartPoint->getX(), StartPoint->getY(), Width, Heigth);
}