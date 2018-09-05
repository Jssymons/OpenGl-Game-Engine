#pragma once
class Time
{
public:
	static double GetDelta();
	static void SetDelta(double d);
private:
	static double delta;
};

