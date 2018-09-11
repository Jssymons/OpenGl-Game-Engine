#pragma once

#include "Texture.h"
#include <vector>
#include <glm\glm.hpp>

class TextureAtlas 
{
public:
	TextureAtlas(std::string fileName, GLuint atlasSize, GLuint textureSize);
	std::vector<GLfloat> GetTextureCoords(glm::vec2 location);
	Texture texture;
private:
	GLuint atlasSize;
	GLuint textureSize;
};

