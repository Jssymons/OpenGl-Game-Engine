#include "Mesh.h"

Mesh::Mesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenBuffers(1, &tbo);
	glGenBuffers(1, &instanceVbo);
}

void Mesh::AddVertices(std::vector<Vertex> vertices, std::vector<glm::vec2> textureCoordianates, std::vector<GLuint> indices)
{
	std::vector<GLfloat> vertexData = ModellingUtil::VertexVectorToFloatVector(vertices);
	std::vector<GLfloat> textureCoordinateData = ModellingUtil::Vector2ToFloatVector(textureCoordianates);
	AddVertices(vertexData, textureCoordinateData, indices);
}

void Mesh::AddVertices(std::vector<GLfloat> vertices, std::vector<GLfloat> textureCoordinates, std::vector<GLuint> indices) {
	size = indices.size();

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(textureCoordinates), textureCoordinates.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::BufferInstances(std::vector<glm::vec3> instances) {
	glBindBuffer(GL_ARRAY_BUFFER, instanceVbo);
	glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(instances[0]), instances.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw(int instanceCount)
{
	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0, instanceCount);
	glBindVertexArray(0);
}