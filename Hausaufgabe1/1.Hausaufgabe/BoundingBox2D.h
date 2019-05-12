#ifndef BOUNDINGBOX2D_H
#define BOUNDINGBOX2D_H


class Point2D;

class BoundingBox2D
{
public:
	BoundingBox2D();
	BoundingBox2D(Point2D& start, double width, double height);
	~BoundingBox2D();
	double getWidth() const;
	double getHeight() const;
	Point2D* getStartPoint() const;
	void uniteWith(const BoundingBox2D& other);
private:
	Point2D* StartPoint;
	double Width;
	double Height;
};

#endif // !BOUNDINGBOX2D_H