#pragma once

#ifndef __gl_h_
#include <GL\glew.h>
#endif // !__gl_h_

#include <vector>
#include "Vertex.h"

class ModellingUtil
{
public:
	static std::vector<GLfloat> ModellingUtil::VertexVectorToFloatVector(std::vector<Vertex> vertices);
};

