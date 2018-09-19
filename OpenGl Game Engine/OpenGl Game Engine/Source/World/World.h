#pragma once
#include "Chunks\Chunk.h"
#include "../../Globals.h"
class World
{
public:
	World();
	void Create(std::vector<Model>* models);
	Chunk* ChunkAt(int x, int z);
	Block* World::GetBlockAt(glm::vec3 position);
private:
	std::vector<std::vector<Chunk>> chunks;
	Random random;
};

