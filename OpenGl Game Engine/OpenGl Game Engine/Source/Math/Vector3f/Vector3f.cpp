#include "Vector3f.h"

Vector3f::Vector3f(double xVal, double yVal, double zVal)
{
	x = xVal;
	y = yVal;
	z = zVal;
}

double Vector3f::Length()
{
	return std::sqrt(x * x + y * y + z * z);
}

double Vector3f::Dot(Vector3f r)
{
	return x * r.GetX() + y * r.GetY() + y * r.GetZ();
}

Vector3f Vector3f::Cross(Vector3f r)
{
	double _x = y * r.GetZ() - z * r.GetY();
	double _y = z * r.GetX() - x * r.GetZ();
	double _z = x * r.GetY() - y * r.GetX();

	return Vector3f(_x, _y, _z);
}

Vector3f Vector3f::Normalize()
{
	double len = Length();

	x /= len;
	y /= len;
	z /= len;

	return Vector3f(x, y, z);
}

Vector3f Vector3f::Rotate(double angle)
{
	return Vector3f(0, 0, 0);
}

Vector3f Vector3f::Add(Vector3f r)
{
	return Vector3f(x + r.GetX(), y + r.GetY(), z + r.GetZ());
}

Vector3f Vector3f::Add(double r)
{
	return Vector3f(x + r, y + r, z + r);
}

Vector3f Vector3f::Subtract(Vector3f r)
{
	return Vector3f(x - r.GetX(), y - r.GetY(), z - r.GetZ());
}

Vector3f Vector3f::Subtract(double r)
{
	return Vector3f(x - r, y - r, z - r);
}

Vector3f Vector3f::Multiply(Vector3f r)
{
	return Vector3f(x * r.GetX(), y * r.GetY(), z * r.GetZ());
}

Vector3f Vector3f::Multiply(double r)
{
	return Vector3f(x * r, y * r, z * r);
}

Vector3f Vector3f::Divide(Vector3f r)
{
	return Vector3f(x / r.GetX(), y / r.GetY(), z / r.GetZ());
}

Vector3f Vector3f::Divide(double r)
{
	return Vector3f(x / r, y / r, z / r);
}

void Vector3f::SetX(double xVal)
{
	x = xVal;
}

void Vector3f::SetY(double yVal)
{
	y = yVal;
}

void Vector3f::SetZ(double zVal)
{
	z = zVal;
}

double Vector3f::GetX()
{
	return x;
}

double Vector3f::GetY()
{
	return y;
}

double Vector3f::GetZ()
{
	return z;
}