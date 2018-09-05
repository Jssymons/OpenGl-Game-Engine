#pragma once
#include "Vertex.h"
#include "ModellingUtil.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	void AddVertices(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void BufferInstances(std::vector<glm::vec3> instances);
	void Draw(int instanceCount);
private:
	GLuint vbo, ibo, vao, instanceVbo;
	int size;
};

