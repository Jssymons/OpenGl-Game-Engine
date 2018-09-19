#include "Block.h"

Block::Block() {}

Block::Block(glm::vec3 position, BlockType type, bool isVisible)
{
	Block::position = position;
	Block::isVisible = isVisible;
	blockType = type;
}

glm::vec3 Block::GetPosition()
{
	return position;
}

BlockType Block::GetBlockType()
{
	return blockType;
}

void Block::SetBlockType(BlockType type)
{
	blockType = type;
}

bool Block::IsVisible()
{
	return isVisible && (blockType != BlockType::None);
}

void Block::SetVisible(bool visible)
{
	isVisible = visible;
}