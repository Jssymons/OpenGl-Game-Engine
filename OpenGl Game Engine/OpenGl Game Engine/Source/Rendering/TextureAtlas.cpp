#include "TextureAtlas.h"
#include "ResourceLoader.h"

TextureAtlas::TextureAtlas(std::string fileName, GLuint atlasSize, GLuint textureSize) 
	: texture(ResourceLoader::LoadTexture(fileName)) 
{
	TextureAtlas::atlasSize = atlasSize;
	TextureAtlas::textureSize = textureSize;
}


std::vector<GLfloat> TextureAtlas::GetTextureCoords(glm::vec2 location) {
	static auto texturesPerRow = atlasSize / textureSize;
	static auto unitSize = 1.0f / (float)texturesPerRow;

	auto xMin = location.x * unitSize;
	auto yMin = 1.0f - (location.y * unitSize);

	auto xMax = xMin + unitSize;
	auto yMax = yMin - unitSize;

	return
	{
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
}