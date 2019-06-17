#include "House.h"

House::House(Point3D refPoint, double cWidth, double cDepth, double cHeight, double prismHeight, Length::Unit unit)
	:refPoint(refPoint), cWidth(cWidth), cDepth(cDepth), cHeight(cHeight), prismHeight(prismHeight)
{
	this->Counter++;
}

House::~House()
{
}

double House::getVolume(Length::Unit unit) const
{
	double volume = 0.0, cuboidVolume = 0.0, prismVolume = 0.0;
	cuboidVolume = this->cWidth * this->cHeight * this->cDepth;
	prismVolume = 0.5 * cDepth * cWidth * prismHeight;
	volume = cuboidVolume + prismVolume;
	return Length(volume, unit).getValue();
}

double House::getSurface(Length::Unit unit) const
{
	double cuboidSurface = 2 * ((this->cWidth * this->cDepth) + (this->cWidth * this->cHeight) + (this->cDepth * this->cHeight));
	double triangleSurface = 2 * this->cWidth * this->cDepth;
	//remove the area where they would sit on each other
	double surface = cuboidSurface + triangleSurface - this->cWidth * this->cDepth;
	return Length(surface, unit).getValue();
}

Point3D House::getLocation() const
{
	return Point3D(this->cDepth / 2, this->cWidth / 2, (this->cHeight / 2) + (1 / 3) * prismHeight);
}

const char* House::getBodyName()
{
	return "house";
}

Body* House::createByDialog()
{
	cout << "create house:" << endl << endl;

	double cWidth = 0.0; double cHeight = 0.0; double cDepth = 0.0;
	cout << "create cuboid:" << endl << endl;

	cout << "Input the cWidth: \t";
	while(cWidth == 0.0)
	{
		cin >> cWidth;
		if(cWidth == 0.0)
			cout << "Size cant be 0";
	}
	cWidth = abs(cWidth);

	cout << "Input the cHeight: \t";
	while(cHeight == 0.0)
	{
		cin >> cHeight;
		if(cHeight == 0.0)
			cout << "Size cant be 0";
	}
	cHeight = abs(cHeight);

	cout << "Input the cDepth: \t";
	while(cDepth == 0.0)
	{
		cin >> cDepth;
		if(cDepth == 0.0)
			cout << "Size cant be 0";
	}
	cDepth = abs(cDepth);

	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - lower front left corner" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	House* t_house = new House(Point3D(x, y, z), cWidth, cDepth, cHeight, Length::METRE);
	return t_house;
}
