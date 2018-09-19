#pragma once
#include <glm\glm.hpp>
#include "BlockType.h"

class Block
{
public:
	Block();
	Block(glm::vec3 position, BlockType type, bool isVisible);
	glm::vec3 GetPosition();
	BlockType GetBlockType();
	void SetBlockType(BlockType type);
	bool IsVisible();
	void SetVisible(bool visible);
private:
	glm::vec3 position;
	BlockType blockType;
	bool isVisible;
};

