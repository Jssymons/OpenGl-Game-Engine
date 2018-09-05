#include "RenderUtil.h"

#ifndef __gl_h_
#include <GL\glew.h>
#endif // !__gl_h_

void RenderUtil::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::InitGraphics()
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_FRAMEBUFFER_SRGB);
}

char* RenderUtil::GetOpenGlVersion()
{
	return (char*)glGetString(GL_VERSION);
}