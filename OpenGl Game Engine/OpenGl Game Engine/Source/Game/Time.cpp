#include "Time.h"

double Time::delta;

double Time::GetDelta()
{
	return delta;
}

void Time::SetDelta(double d)
{
	delta += d;
}