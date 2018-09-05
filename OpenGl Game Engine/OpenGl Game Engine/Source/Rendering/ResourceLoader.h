#pragma once
#include "../Modelling/Mesh.h"

#ifndef __gl_h_
#include <GL\glew.h>
#endif // !__gl_h_

#include <string>

class ResourceLoader {
public:
	static Mesh LoadMesh(std::string fileName);
	static GLuint LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	static GLuint CompileShader(const GLchar* source, GLenum type);
	static std::string GetShaderSource(const std::string sourceFile);
	static GLuint CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
private:
	static std::vector<std::string> SplitString(std::string fileName, char n);
};