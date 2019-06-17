#pragma once

class Drawer2D
{
private : 
	double X_Start, Y_Start, X_End, Y_End;

public:
	Drawer2D();
	~Drawer2D(); 
	virtual void DrawPoint(double X, double Y) const = 0;
	virtual void DrawLine(double x_Start, double y_Start, double x_End, double y_End) const =0;
	virtual void DrawBoundingBox(double x, double y, double Width, double Heigth) const =0;
};