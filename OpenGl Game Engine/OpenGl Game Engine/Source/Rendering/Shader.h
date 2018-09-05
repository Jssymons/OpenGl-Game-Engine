#pragma once

#ifndef __gl_h_
#include <GL\glew.h>
#endif // !__gl_h_

#include <glm\glm.hpp>
#include <string>
#include <map>

class Shader
{
public:
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	void Bind();
	void UnBind();
	void AddUniform(char* uniform);
	void AddAttribute(char* attrib);
	void SetAttribute(char* attrib, glm::vec3 value);
	void SetUniformi(char* uniform, GLuint value);
	void SetUniformf(char* uniform, GLfloat value);
	void SetUniform(const char* uniform, glm::vec3 value);
	void SetUniform(char* uniform, glm::mat4 matrix);
	double GetUniform(char* uniform);
	GLuint GetId();
private:
	GLuint programId;
	std::map<std::string, GLuint> uniforms;
	std::map<std::string, GLuint> attributes;
};

