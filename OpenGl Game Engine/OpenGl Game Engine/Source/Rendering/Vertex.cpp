#include "Vertex.h"

Vertex::Vertex(glm::vec3 pos)
{
	Vertex::pos = pos;
}

glm::vec3 Vertex::GetPos()
{
	return pos;
}

void Vertex::SetPos(glm::vec3 pos)
{
	Vertex::pos = pos;
}