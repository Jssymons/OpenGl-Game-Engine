#include "ResourceLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

Texture ResourceLoader::LoadTexture(std::string fileName) {
	std::vector<std::string> splitFileName = SplitString(fileName, '.');
	std::string extension = splitFileName[splitFileName.size() - 1];

	if (extension != "bmp") 
	{
		printf("Error: file format not supported for texture: %s", extension);
		throw std::runtime_error("Error: file format not supported for texture: " + extension);
	}

	std::string filePath = "Data/Textures/" + fileName;

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width;
	unsigned int height;

	FILE* file = new FILE();
	fopen_s(&file, filePath.c_str(), "rb");

	if (!file) {
		throw std::runtime_error("Error opening image: " + filePath);
	}

	if (fread(header, 1, 54, file) != 54) {
		throw std::runtime_error("Error reading image header: " + filePath);
	}

	if (header[0] != 'B' || header[1] != 'M') {
		throw std::runtime_error("Image is not a BMP: " + filePath);
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	unsigned char* data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	return Texture(textureId);
}

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
	std::vector<glm::vec3> vertexCoordData;
	std::vector<glm::vec2> textureCoordData;

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
			vertexCoordData.push_back(glm::vec3(
					std::stod(tokens[1]),
					std::stod(tokens[2]),
					std::stod(tokens[3])
				));
		}
		else if (tokens[0] == "vt") {
			textureCoordData.push_back(glm::vec2(
					std::stod(tokens[1]),
					std::stod(tokens[2])
				));
		}
		else if (tokens[0] == "f")
		{
			indexData.push_back((GLuint)std::stoi(&tokens[1].front()) - 1);
			indexData.push_back((GLuint)std::stoi(&tokens[2].front()) - 1);
			indexData.push_back((GLuint)std::stoi(&tokens[3].front()) - 1);
		}

	}

	for (int i = 0; i < vertexCoordData.size(); i++) {
		vertexData.push_back(Vertex(vertexCoordData[i]));
	}

	Mesh m;
	m.AddVertices(vertexData, textureCoordData, indexData);
	return m;
}

Mesh ResourceLoader::CubePrimitive(TextureAtlas atlas, BlockType blockType) {
	std::vector<GLfloat> vertexPositions =
	{
		//Back
		1, -1, -1,
		-1, -1, -1,
		-1, 1, -1,
		1, 1, -1,

		//Right-Side
		1, -1, 1,
		1, -1, -1,
		1, 1, -1,
		1, 1, 1,

		//Front
		-1, -1, 1,
		1, -1, 1,
		1, 1, 1,
		-1, 1, 1,

		//Left
		-1, -1, -1,
		-1, -1, 1,
		-1, 1, 1,
		-1, 1, -1,

		//Top
		-1, 1, 1,
		1, 1, 1,
		1, 1, -1,
		-1, 1, -1,

		//Bottom
		-1, -1, -1,
		1, -1, -1,
		1, -1, 1,
		-1, -1, 1
	};

	std::vector<GLfloat> textureCoords;

	std::vector<GLfloat> back;
	std::vector<GLfloat> right;
	std::vector<GLfloat> front;
	std::vector<GLfloat> left;
	std::vector<GLfloat> top;
	std::vector<GLfloat> bottom;

	switch (blockType) {
	case (BlockType::Dirt) :
		back = atlas.GetTextureCoords(	{ 2, 0 });
		right = atlas.GetTextureCoords(	{ 2, 0 });
		front = atlas.GetTextureCoords(	{ 2, 0 });
		left = atlas.GetTextureCoords(	{ 2, 0 });
		top = atlas.GetTextureCoords(	{ 2, 0 });
		bottom = atlas.GetTextureCoords({ 2, 0 });
		break;
	case (BlockType::Grass) :
		back = atlas.GetTextureCoords({ 3, 0 });
		right = atlas.GetTextureCoords({ 3, 0 });
		front = atlas.GetTextureCoords({ 3, 0 });
		left = atlas.GetTextureCoords({ 3, 0 });
		top = atlas.GetTextureCoords({ 0, 0 });
		bottom = atlas.GetTextureCoords({ 2, 0 });
		break;
	case (BlockType::Stone) :
		back = atlas.GetTextureCoords({ 1, 0 });
		right = atlas.GetTextureCoords({ 1, 0 });
		front = atlas.GetTextureCoords({ 1, 0 });
		left = atlas.GetTextureCoords({ 1, 0 });
		top = atlas.GetTextureCoords({ 1, 0 });
		bottom = atlas.GetTextureCoords({ 1, 0 });
		break;
	case (BlockType::Bedrock) :
		back = atlas.GetTextureCoords({ 5, 2 });
		right = atlas.GetTextureCoords({ 5, 2 });
		front = atlas.GetTextureCoords({ 5, 2 });
		left = atlas.GetTextureCoords({ 5, 2 });
		top = atlas.GetTextureCoords({ 5, 2 });
		bottom = atlas.GetTextureCoords({ 5, 2 });
		break;
	case (BlockType::Trunk) :
		back = atlas.GetTextureCoords({ 4, 1 });
		right = atlas.GetTextureCoords({ 4, 1 });
		front = atlas.GetTextureCoords({ 4, 1 });
		left = atlas.GetTextureCoords({ 4, 1 });
		top = atlas.GetTextureCoords({ 5, 1 });
		bottom = atlas.GetTextureCoords({ 5, 1 });
		break;
	case (BlockType::Leaves) :
		back = atlas.GetTextureCoords({ 5, 3 });
		right = atlas.GetTextureCoords({ 5, 3 });
		front = atlas.GetTextureCoords({ 5, 3 });
		left = atlas.GetTextureCoords({ 5, 3 });
		top = atlas.GetTextureCoords({ 5, 3 });
		bottom = atlas.GetTextureCoords({ 5, 3 });
		break;
	}

	textureCoords.insert(textureCoords.end(), back.begin(), back.end());
	textureCoords.insert(textureCoords.end(), right.begin(), right.end());
	textureCoords.insert(textureCoords.end(), front.begin(), front.end());
	textureCoords.insert(textureCoords.end(), left.begin(), left.end());
	textureCoords.insert(textureCoords.end(), top.begin(), top.end());
	textureCoords.insert(textureCoords.end(), bottom.begin(), bottom.end());

	std::vector<GLuint> indices =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	Mesh m;
	m.AddVertices(vertexPositions, textureCoords, indices);
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