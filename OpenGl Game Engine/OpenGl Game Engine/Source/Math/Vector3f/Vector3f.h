#pragma once
#include <string>

class Vector3f
{
public:
	Vector3f(double xVal, double yVal, double zVal);
	double Length();
	double Dot(Vector3f r);
	Vector3f Cross(Vector3f r);
	Vector3f Normalize();
	Vector3f Rotate(double angle);
	Vector3f Add(Vector3f r);
	Vector3f Add(double r);
	Vector3f Subtract(Vector3f r);
	Vector3f Subtract(double r);
	Vector3f Multiply(Vector3f r);
	Vector3f Multiply(double r);
	Vector3f Divide(Vector3f r);
	Vector3f Divide(double r);
	void SetX(double xVal);
	void SetY(double yVal);
	void SetZ(double zVal);
	double GetX();
	double GetY();
	double GetZ();
	std::string ToString();
private:
	double x;
	double y;
	double z;
};

