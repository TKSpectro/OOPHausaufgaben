#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include"Drawer2D.h"
#include"Turtleizer_CPP-master/Turtleizer.h"
#include"Line2D.h"
#include"Point2D.h" 
class DrawIt :
	public Drawer2D
{
public:
	DrawIt(double x_Start = 0.0, double y_Start = 0.0, double x_End = 0.0, double y_End = 0.0);
	~DrawIt();
	void DrawLine(double x_Start, double y_Start, double x_End, double y_End) const;
	void DrawPoint(double X, double Y) const;
	void DrawBoundingBox(double x, double y, double Width, double Heigth);
private:
	double X_Start, Y_Start, X_End, Y_End;
};

