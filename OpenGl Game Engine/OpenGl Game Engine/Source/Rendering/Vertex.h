#pragma once
#include <glm\glm.hpp>

class Vertex
{
public:
	Vertex(glm::vec3 pos);
	glm::vec3 GetPos();
	void SetPos(glm::vec3);
	static const int SIZE = 3;
private:
	glm::vec3 pos;
};

