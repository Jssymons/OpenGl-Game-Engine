#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "../../Globals.h"

#ifndef __gl_h_
#include <GL\glew.h>
#endif // !__gl_h_

#include <string>

class ResourceLoader {
public:
	static Texture LoadTexture(std::string fileName);
	static Mesh LoadMesh(std::string fileName);
	static GLuint LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	static Mesh ResourceLoader::CubePrimitive(TextureAtlas atlas, Globals::BLOCK_TYPES blockType);
	static GLuint CompileShader(const GLchar* source, GLenum type);
	static std::string GetShaderSource(const std::string sourceFile);
	static GLuint CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
private:
	static std::vector<std::string> SplitString(std::string fileName, char n);
};