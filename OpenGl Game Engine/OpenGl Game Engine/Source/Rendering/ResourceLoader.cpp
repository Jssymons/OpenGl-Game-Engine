#include "ResourceLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh ResourceLoader::LoadMesh(std::string fileName)
{
	std::vector<std::string> splitFileName = SplitString(fileName, '.');
	std::string extension = splitFileName[splitFileName.size() - 1];

	if (extension != "obj")
	{
		printf("Error: file format not supported for mesh data: %s", extension);
		throw std::runtime_error("Error: file format not supported for mesh data: " + extension);
	}

	std::vector<Vertex> vertexData;
	std::vector<GLuint> indexData;

	std::ifstream inFile("Data/Models/" + fileName);
	std::string line;
	while (std::getline(inFile, line))
	{
		std::istringstream stream(line);
		std::vector<std::string> tokens = SplitString(line, ' ');

		if (tokens.size() == 0 || tokens[0] == "#")
			continue;
		else if (tokens[0] == "v")
		{
			vertexData.push_back(Vertex(glm::vec3(
				std::stod(tokens[1]),
				std::stod(tokens[2]),
				std::stod(tokens[3])
				)));
		}
		else if (tokens[0] == "f")
		{
			indexData.push_back((GLuint)std::stoi(tokens[1]) - 1);
			indexData.push_back((GLuint)std::stoi(tokens[2]) - 1);
			indexData.push_back((GLuint)std::stoi(tokens[3]) - 1);
		}
	}

	Mesh m;
	m.AddVertices(vertexData, indexData);
	return m;
}

GLuint ResourceLoader::LoadShader(const std::string & vertexShaderFile, const std::string & fragmentShaderFile)
{
	std::string vertexSource = GetShaderSource(vertexShaderFile);
	std::string fragmentSource = GetShaderSource(fragmentShaderFile);
	GLuint vertexShaderID = CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
	GLuint programID = CreateProgram(vertexShaderID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

GLuint ResourceLoader::CompileShader(const GLchar* source, GLenum type)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	GLint isSuccess;
	GLchar infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &isSuccess);

	if (!isSuccess)
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		throw std::runtime_error("Error compiling shader: " + std::string(infoLog));
	}

	return id;
}

std::string ResourceLoader::GetShaderSource(const std::string sourceFile)
{
	std::ifstream inFile("Data/Shaders/" + sourceFile);
	std::string source;
	std::stringstream stringStream;

	if (!inFile.is_open())
	{
		throw std::runtime_error("Could not open file: " + sourceFile);
	}

	stringStream << inFile.rdbuf();
	source = stringStream.str();

	return source;
}

GLuint ResourceLoader::CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
	GLuint id = glCreateProgram();
	glAttachShader(id, vertexShaderID);
	glAttachShader(id, fragmentShaderID);
	glLinkProgram(id);

	return id;
}

std::vector<std::string> ResourceLoader::SplitString(std::string s, char n)
{
	std::vector<std::string> splitString;

	int i = 0;
	int pos = s.find(n);
	while (pos != std::string::npos) {
		std::string stringToAdd = s.substr(i, pos - i);

		if (stringToAdd != "")
			splitString.push_back(stringToAdd);

		i = ++pos;
		pos = s.find(n, pos);

		if (pos == std::string::npos)
		{
			stringToAdd = s.substr(i, s.length());

			if (stringToAdd != "")
				splitString.push_back(stringToAdd);
		}
	}
	return splitString;
}