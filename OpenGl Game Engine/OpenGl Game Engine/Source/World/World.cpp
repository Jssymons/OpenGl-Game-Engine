#include "World.h"
#include <math.h>


World::World()
{

}

void World::Create(std::vector<Model>* models)
{
	for (int x = 0; x < Globals::CHUNK_RADIUS * 2; x++)
	{
		std::vector<Chunk> yChunks;
		for (int y = 0; y < Globals::CHUNK_RADIUS * 2; y++)
		{
			yChunks.push_back(Chunk(models, &random, x, y));
		}
		chunks.push_back(yChunks);
	}
}

Chunk* World::ChunkAt(int x, int z)
{
	return &chunks[x][z];
}

Block* World::GetBlockAt(glm::vec3 position)
{
	int chunkX, chunkZ;
	chunkX = position.x / Globals::CHUNK_WIDTH;
	chunkZ = position.z / Globals::CHUNK_WIDTH;
	/*chunkX = floor(position.x / Globals::CHUNK_WIDTH) + Globals::CHUNK_RADIUS - 1;
	chunkZ = floor(position.z / Globals::CHUNK_WIDTH) + Globals::CHUNK_RADIUS - 1;*/

	int chunkLocalX, chunkLocalY, chunkLocalZ;
	chunkLocalX = (int)round(position.x) % Globals::CHUNK_WIDTH;
	chunkLocalY = ((int)round(position.y) % Globals::CHUNK_WIDTH) + Globals::CHUNK_HEIGHT / 2;
	chunkLocalZ = (int)round(position.z) % Globals::CHUNK_WIDTH;

	if (chunkLocalX < 0)
	{
		chunkLocalX = Globals::CHUNK_WIDTH - chunkLocalX;
	}

	if (chunkLocalY < 0)
	{
		chunkLocalY = Globals::CHUNK_WIDTH - chunkLocalY;
	}

	if (chunkLocalZ < 0)
	{
		chunkLocalZ = Globals::CHUNK_WIDTH - chunkLocalZ;
	}

	if (chunks[chunkX][chunkZ].HasVisibleBlockAt(chunkLocalX, chunkLocalY, chunkLocalZ))
	{
		return chunks[chunkX][chunkZ].GetBlock(chunkLocalX, chunkLocalY, chunkLocalZ);
	}
	else
	{
		return nullptr;
	}
}