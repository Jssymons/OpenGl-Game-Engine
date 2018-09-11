#include "ModellingUtil.h"

std::vector<GLfloat> ModellingUtil::VertexVectorToFloatVector(std::vector<Vertex> vertices)
{
	std::vector<GLfloat> floatVector;

	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec3 pos = vertices[i].GetPos();
		floatVector.push_back(pos.x);
		floatVector.push_back(pos.y);
		floatVector.push_back(pos.z);
	}

	return floatVector;
}

std::vector<GLfloat> ModellingUtil::Vector2ToFloatVector(std::vector<glm::vec2> vectors) {
	std::vector<GLfloat> floatVector;

	for (int i = 0; i < vectors.size(); i++)
	{
		floatVector.push_back(vectors[i].x);
		floatVector.push_back(vectors[i].y);
	}

	return floatVector;
}