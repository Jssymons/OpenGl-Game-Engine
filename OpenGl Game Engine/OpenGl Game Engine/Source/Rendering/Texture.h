#pragma once

#ifndef __gl_h_
#include <GL\glew.h>
#endif // !__gl_h_

class Texture
{
public:
	Texture(int textureId);
	int GetId();
	void Bind();
private:
	int id;
};

