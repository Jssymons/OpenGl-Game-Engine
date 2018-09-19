#pragma once

#include "../Blocks/Block.h"
#include "../../Math/Array3D.h"
#include "../../../Globals.h"
#include "../../Math/Random.h"
#include "../../Rendering/Model.h"
#include "../Blocks/Block.h"
#include <vector>

class Chunk
{
public:
	Chunk(std::vector<Model>* models, Random* random, int xLocation, int zLocation);
	void RemoveBlockAt(glm::vec3 location);
	bool HasVisibleBlockAt(int x, int y, int z);
	Block* GetBlock(int x, int y, int z);
	BlockType GetBlockType(int x, int y, int z);
private:
	int xOffset, zOffset, chunkBottom, chunkTop;
	std::vector<Model>* models;
	Random* random;
	Array3D<Block> blocks;
	void GenerateBlocks();
	void GenerateTrees();
	void CullInvisibleBlocks();
	void BuildChunkMesh();
};

