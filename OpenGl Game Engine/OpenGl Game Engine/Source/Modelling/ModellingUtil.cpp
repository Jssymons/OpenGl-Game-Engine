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