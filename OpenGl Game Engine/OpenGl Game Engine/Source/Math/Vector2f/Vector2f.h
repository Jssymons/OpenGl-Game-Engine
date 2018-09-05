#pragma once
#include <string>

class Vector2f
{
public:
	Vector2f(double x, double y);
	double Length();
	double Dot(Vector2f r);
	Vector2f Normalize();
	Vector2f Rotate(double angle);
	Vector2f Add(Vector2f r);
	Vector2f Add(double r);
	Vector2f Subtract(Vector2f r);
	Vector2f Subtract(double r);
	Vector2f Multiply(Vector2f r);
	Vector2f Multiply(double r);
	Vector2f Divide(Vector2f r);
	Vector2f Divide(double r);
	void SetX(double xVal);
	void SetY(double yVal);
	double GetX();
	double GetY();
	std::string ToString();
private:
	double x;
	double y;
};

