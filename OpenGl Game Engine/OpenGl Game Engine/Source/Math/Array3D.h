#pragma once
#include <vector>

template <typename element>
class Array3D
{
public:
	Array3D(int width, int length, int height)
	{
		items = std::vector<element>(length * width * height);
		Array3D<element>::height = height;
		Array3D<element>::length = length;
		Array3D<element>::width = width;
	}

	element* Array3D<element>::at(int x, int y, int z)
	{
		return &items[(y*length*width) + (z * length) + x];
	}
private:
	int width, length, height;
	std::vector<element> items;
};

