#pragma once
#include "Vertex.h"
#include "ModellingUtil.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	void AddVertices(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void BufferInstances(glm::vec3* offsets);
	void Draw();
private:
	GLuint vbo, ibo, vao, instanceVbo;
	int size;
};

