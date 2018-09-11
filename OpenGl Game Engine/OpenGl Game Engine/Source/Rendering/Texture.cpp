#include "Texture.h"

Texture::Texture(int textureId)
{
	id = textureId;
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

int Texture::GetId() {
	return id;
}