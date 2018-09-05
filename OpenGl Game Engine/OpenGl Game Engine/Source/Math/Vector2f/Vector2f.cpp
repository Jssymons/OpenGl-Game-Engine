#include "Vector2f.h"
#include <Math\Util.h>

Vector2f::Vector2f(double xVal, double yVal)
{
	x = xVal;
	y = yVal;
}

double Vector2f::Length()
{
	return std::sqrt(x * x + y * y);
}

double Vector2f::Dot(Vector2f r)
{
	return x * r.GetX() + y * r.GetY();
}

Vector2f Vector2f::Normalize()
{
	double len = Length();

	x /= len;
	y /= len;

	return Vector2f(x, y);
}

Vector2f Vector2f::Rotate(double angle)
{
	double radians = Util::To_Radians(angle);
	float cos = std::cos(radians);
	float sin = std::sin(radians);


	return Vector2f(x * cos - y * sin, x * sin + y * cos);
}

Vector2f Vector2f::Add(Vector2f r)
{
	return Vector2f(x + r.GetX(), y + r.GetY());
}

Vector2f Vector2f::Add(double r)
{
	return Vector2f(x + r, y + r);
}

Vector2f Vector2f::Subtract(Vector2f r)
{
	return Vector2f(x - r.GetX(), y - r.GetY());
}

Vector2f Vector2f::Subtract(double r)
{
	return Vector2f(x - r, y - r);
}

Vector2f Vector2f::Multiply(Vector2f r)
{
	return Vector2f(x * r.GetX(), y * r.GetY());
}

Vector2f Vector2f::Multiply(double r)
{
	return Vector2f(x * r, y * r);
}

Vector2f Vector2f::Divide(Vector2f r)
{
	return Vector2f(x / r.GetX(), y / r.GetY());
}

Vector2f Vector2f::Divide(double r)
{
	return Vector2f(x / r, y / r);
}

void Vector2f::SetX(double xVal)
{
	x = xVal;
}

void Vector2f::SetY(double yVal)
{
	y = yVal;
}

double Vector2f::GetX()
{
	return x;
}

double Vector2f::GetY()
{
	return y;
}

std::string Vector2f::ToString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}