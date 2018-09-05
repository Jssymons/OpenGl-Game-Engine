#include "Shader.h"
#include "ResourceLoader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	programId = ResourceLoader::LoadShader(vertexShaderFile, fragmentShaderFile);
}

void Shader::Bind()
{
	glUseProgram(programId);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

void Shader::AddUniform(char* uniform)
{
	GLuint uniformLocation = glGetUniformLocation(programId, uniform);

	if (uniformLocation == -1)
	{
		printf("Error: could not find uniform '%s'", uniform);
		throw std::runtime_error("Error: could not find uniform " + std::string(uniform));
	}

	uniforms[uniform] = uniformLocation;
}

double Shader::GetUniform(char* uniform)
{
	GLfloat value;
	glGetUniformfv(programId, uniforms.find(uniform)->second, &value);
	return (double)value;
}

void Shader::AddAttribute(char* attrib)
{
	GLuint index = attributes.size() + 1;
	attributes[attrib] = index;
	glBindAttribLocation(programId, index, attrib);
}

void Shader::SetAttribute(char * attrib, glm::vec3 value)
{
	GLfloat att[] = { value.x, value.y, value.z };
	glVertexAttrib3fv(attributes.find(attrib)->second, att);
}

void Shader::SetUniformi(char * uniform, GLuint value)
{
	glUniform1i(uniforms.find(uniform)->second, value);
}

void Shader::SetUniformf(char * uniform, GLfloat value)
{
	glUniform1f(uniforms.find(uniform)->second, value);
}

void Shader::SetUniform(const char * uniform, glm::vec3 vector)
{
	glUniform3f(uniforms.find(uniform)->second, vector.x, vector.y, vector.z);
}

void Shader::SetUniform(char * uniform, glm::mat4 matrix)
{
	glUniformMatrix4fv(uniforms.find(uniform)->second, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::GetId()
{
	return programId;
}
