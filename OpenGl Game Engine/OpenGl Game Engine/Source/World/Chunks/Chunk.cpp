#include "Chunk.h"

Chunk::Chunk(std::vector<Model>* models, int xLocation, int zLocation)
{
	int xStart = xLocation * Globals::CHUNK_WIDTH;
	int xEnd = xStart + Globals::CHUNK_WIDTH;
	int yStart = -Globals::CHUNK_HEIGHT;
	int yEnd = 0;
	int zStart = zLocation * Globals::CHUNK_WIDTH;
	int zEnd = zStart + Globals::CHUNK_WIDTH;

	// Build chunk
	int counter = 0;
	for (int z = zStart; z < zEnd; z++)
	{
		for (int y = yStart; y < yEnd; y++)
		{
			for (int x = xStart; x < xEnd; x++)
			{
				if (z > zStart && z < zEnd - 1
					&& x > xStart && x < xEnd - 1
					&& y > yStart && y < yEnd - 1)
				{
					continue;
				}

				glm::vec3 currentPos = glm::vec3(x * 2.0f, y * 2.0f, z * 2.0f);

				if (y == -1)
				{
					models->at(BlockType::Grass).AddInstance(currentPos);
				}
				else if (y > -(Globals::CHUNK_HEIGHT / 3))
				{
					models->at(BlockType::Dirt).AddInstance(currentPos);
				}
				else if (y > -(Globals::CHUNK_HEIGHT / 3) * 2)
				{
					if (random.IntInRange(0, 4) == 0)
					{
						models->at(BlockType::Stone).AddInstance(currentPos);
					}
					else
					{
						models->at(BlockType::Dirt).AddInstance(currentPos);
					}
				}
				else if (y > -Globals::CHUNK_HEIGHT + 1)
				{
					models->at(BlockType::Stone).AddInstance(currentPos);
				}
				else
				{
					models->at(BlockType::Bedrock).AddInstance(currentPos);
				}

				counter++;
			}
		}
	}

	//// Create trees
	int baseTerrainHeight = yEnd;
	for (int z = zStart; z < zEnd; z = z + 4)
	{
		for (int x = xStart; x < xEnd; x = x + 4)
		{
			if (random.IntInRange(0, 6) == 0)
			{
				// Trunk
				int trunkHeight = random.IntInRange(4, 10);
				for (int i = 0; i < trunkHeight; i++)
				{
					models->at(BlockType::Trunk).AddInstance(glm::vec3(x * 2.0f, (baseTerrainHeight + i) * 2.0f, z * 2.0f));
				}

				// Leaves
				int foliageWidth = (random.IntInRange(1, 2) * 2) + 1;
				int foliageBottom = baseTerrainHeight + trunkHeight - 1;
				int foliageHeight = random.IntInRange(3, 4);

				for (int ly = 0; ly < foliageHeight; ly++)
				{
					for (int lx = x - (foliageWidth - ly); lx < x + (foliageWidth - ly); lx++)
					{
						for (int lz = z - (foliageWidth - ly); lz < z + (foliageWidth - ly); lz++)
						{
							models->at(BlockType::Leaves).AddInstance(glm::vec3(lx * 2.0f, (ly + foliageBottom) * 2.0f, lz * 2.0f));
						}
					}
				}

			}
		}
	}
}