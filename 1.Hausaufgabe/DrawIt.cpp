#include"DrawIt.h"

DrawIt::DrawIt(double x_Start, double y_Start, double x_End, double y_End)
	:X_Start(x_Start), Y_Start(y_End), X_End(x_End), Y_End(y_End)
{
}

DrawIt::~DrawIt()
{
}

void DrawIt::DrawLine(double x_Start, double y_Start, double x_End, double y_End) const
{
	Point2D p1(x_Start, y_End);
	Point2D p2(x_End, y_End);
	Line2D l1(p1, p2);
	penUp();
	gotoXY(x_Start, y_Start);
	penDown();
	double Angle = l1.getVector().getOrientation();
	double Length = l1.getLength();
	right(90 - Angle);
	forward(Length);
	penUp();
}

void DrawIt :: DrawPoint(double X, double Y) const
{
	Point2D p1(X, Y);
	Point2D p2(X + 0.5, Y);
	penUp();
	gotoXY(X, Y);
	right(90);
	Vector2D Difference = p1.getDifference(p2);
	gotoX(Difference.getX());
	right(90);
	penDown();
	forward(Difference.getY()-0.5);
	right(90);
	forward(Difference.getX()-1);
	right(90);
	forward(Difference.getY()+1);
	right(90);
	forward(Difference.getX() + 1);
	right(Difference.getY() - 0.5);
	penUp();
}
void DrawIt::DrawBoundingBox(double x, double y, double Width, double Heigth)
{
	Point2D p1(x, y);
	penUp();
	gotoXY(x, y);
	penDown();
	forward(Heigth);
	right(90);
	forward(Width);
	right(90);
	forward(Heigth);
	right(90);
	forward(Width);
	penUp();
}