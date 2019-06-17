#include "Cube.h"

int Cube::zähler = 0;

Cube::Cube(Point3D refPoint, double sideSize,Length::Unit unit)
	:refPoint(refPoint), size(Length(sideSize).getValue())
{
	 this->Counter++;
	 zähler++;
}

Cube::~Cube()
{
}

double Cube::getVolume(Length::Unit unit) const
{
	return Length (6 * (size * size),unit).getValue(unit);
}

double Cube::getSurface(Length::Unit unit) const
{
	return Length(size * size * size,unit).getValue();
}

Point3D Cube::getLocation() const
{
	return Point3D(this->refPoint.getX() + size / 2, this->refPoint.getY() + size / 2, this->refPoint.getZ() + size / 2);
}

const char* Cube::getBodyName()
{
	return "cube";
}

Body* Cube::createByDialog()
{
	double size = 0.0;
	cout << "create cube:" << endl << endl;
	
	cout << "Input the side length: \t";
	while(size == 0.0)
	{
		cin >> size;
		if(size == 0.0)
			cout << "size cant be 0";
	}
	size = abs(size);

	double x = 0.0; double y = 0.0; double z = 0.0;
	cout << "Input the reference Point - lower front left corner" << endl;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	cout << "Z: ";
	cin >> z;

	Cube* t_cube = new Cube(Point3D(x,y,z), size, Length::METRE);
	return t_cube;
}
