#pragma once

#include "../../Math/Random.h"
#include "../../../Globals.h"
#include "../../Rendering/Model.h"
#include <vector>

class Chunk
{
public:
	Chunk(std::vector<Model>* models, int xOffset, int zOffset);
private:
	Random random;
};

