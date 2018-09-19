#include "Chunk.h"
#include <glm\ext.hpp>

Chunk::Chunk(std::vector<Model>* models, Random* random, int xLocation, int zLocation)
	: blocks(Globals::CHUNK_WIDTH, Globals::CHUNK_WIDTH, Globals::CHUNK_HEIGHT)
{
	xOffset = xLocation;
	zOffset = zLocation;
	chunkBottom = -Globals::CHUNK_HEIGHT / 2;
	chunkTop = Globals::CHUNK_HEIGHT / 2;
	Chunk::models = models;
	Chunk::random = random;

	GenerateBlocks();
	GenerateTrees();
	CullInvisibleBlocks();
	BuildChunkMesh();
}

void Chunk::RemoveBlockAt(glm::vec3 location)
{
	//printf("Removing block at %s\n", glm::to_string(location).c_str());
}

bool Chunk::HasVisibleBlockAt(int x, int y, int z)
{
	return blocks.at(x, y, z)->IsVisible();
}

void Chunk::GenerateBlocks() 
{
	for (int z = 0; z < Globals::CHUNK_WIDTH; z++)
	{
		for (int y = chunkBottom; y < chunkTop; y++)
		{
			for (int x = 0; x < Globals::CHUNK_WIDTH; x++)
			{
				int worldX = x + xOffset * Globals::CHUNK_WIDTH;
				int worldZ = z + zOffset * Globals::CHUNK_WIDTH;
				int yOffset = y + Globals::CHUNK_HEIGHT / 2;
				glm::vec3 currentPos = glm::vec3(worldX * 2.0f, y * 2.0f, worldZ * 2.0f);
				
				if (y == chunkBottom)
				{
					*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Bedrock, false);
				}
				else if (y < chunkBottom / 2)
				{
					*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Stone, false);
				}
				else if (y < chunkBottom / 3)
				{
					if (random->IntInRange(0, 4) == 0)
					{
						*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Stone, false);
					}
					else
					{
						*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Dirt, false);
					}
				}
				else if (y < 0)
				{
					*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Dirt, false);
				}
				else if (y == 0)
				{
					*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Grass, false);
				}
				else 
				{
					*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::None, false);
				}
			}
		}
	}
}

void Chunk::GenerateTrees()
{
	for (int z = 0; z < Globals::CHUNK_WIDTH; z = z + 4)
	{
		for (int x = 0; x < Globals::CHUNK_WIDTH; x = x + 4)
		{
			if (random->IntInRange(0, 6) == 0)
			{
				int worldXOffset = xOffset * Globals::CHUNK_WIDTH;
				int worldZOffset = zOffset * Globals::CHUNK_WIDTH;
				int worldX = x + worldXOffset;
				int worldZ = z + worldZOffset;

				// Trunk
				int trunkHeight = random->IntInRange(4, 10);
				for (int y = 0; y < trunkHeight; y++)
				{
					int yOffset = y + Globals::CHUNK_HEIGHT / 2;
					glm::vec3 currentPos = glm::vec3(worldX * 2.0f, y * 2.0f, worldZ * 2.0f);
					*blocks.at(x, yOffset, z) = Block(currentPos, BlockType::Trunk, false);
				}

				// Leaves
				int foliageWidth = (random->IntInRange(1, 2) * 2) + 1;
				int foliageBottom = trunkHeight - 1;
				int foliageTop = foliageBottom + random->IntInRange(3, 4);

				int xStart = x - foliageWidth;
				int xEnd = x + foliageWidth;
				int zStart = z - foliageWidth;
				int zEnd = z + foliageWidth;

				for (int ly = foliageBottom; ly < foliageTop; ly++)
				{
					int yOffset = ly + Globals::CHUNK_HEIGHT / 2;
					for (int lx = xStart; lx < xEnd; lx++)
					{
						for (int lz = zStart; lz < zEnd; lz++)
						{
							if (lx >= 0 && lx < Globals::CHUNK_WIDTH && lz >= 0 && lz < Globals::CHUNK_WIDTH)
							{
								glm::vec3 currentPos = glm::vec3((lx + worldXOffset) * 2.0f, ly * 2.0f, (lz + worldZOffset) * 2.0f);
								*blocks.at(lx, yOffset, lz) = Block(currentPos, BlockType::Leaves, false);
							}
						}
					}
				}

			}
		}
	}
}

void Chunk::CullInvisibleBlocks() {
	for (int z = 0; z < Globals::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < Globals::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < Globals::CHUNK_WIDTH; x++)
			{
				Block* block = blocks.at(x, y, z);
				block->SetVisible(GetBlockType(x - 1, y, z) == BlockType::None
					|| GetBlockType(x + 1, y, z) == BlockType::None
					|| GetBlockType(x, y - 1, z) == BlockType::None
					|| GetBlockType(x, y + 1, z) == BlockType::None
					|| GetBlockType(x, y, z - 1) == BlockType::None
					|| GetBlockType(x, y, z + 1) == BlockType::None);
			}
		}
	}
}

void Chunk::BuildChunkMesh()
{
	for (int z = 0; z < Globals::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < Globals::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < Globals::CHUNK_WIDTH; x++)
			{
				Block* block = blocks.at(x, y, z);
				if (block->IsVisible())
				{
					models->at(block->GetBlockType()).AddInstance(block->GetPosition());
				}
			}
		}
	}
}

BlockType Chunk::GetBlockType(int x, int y, int z)
{
	if (x >= 0 && x < Globals::CHUNK_WIDTH
		&& z >= 0 && z < Globals::CHUNK_WIDTH
		&& y >= 0 && y < Globals::CHUNK_HEIGHT)
	{
		return blocks.at(x, y, z)->GetBlockType();
	}
	else
	{
		return BlockType::None;
	}
}


Block* Chunk::GetBlock(int x, int y, int z)
{
	if (x >= 0 && x < Globals::CHUNK_WIDTH
		&& z >= 0 && z < Globals::CHUNK_WIDTH
		&& y >= 0 && y < Globals::CHUNK_HEIGHT)
	{
		return blocks.at(x, y, z);
	}
	else
	{
		return 0;
	}
}