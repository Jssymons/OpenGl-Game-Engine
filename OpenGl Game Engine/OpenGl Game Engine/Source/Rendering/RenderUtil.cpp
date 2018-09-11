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
	glClearColor(0.529f, 0.807f, 0.921f, 0.1f);

	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

void RenderUtil::SetWireframe(bool enabled) {
	if (enabled) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
}

void RenderUtil::SetTextures(bool enabled) {
	if (enabled) {
		glEnable(GL_TEXTURE_2D);
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}
}

char* RenderUtil::GetOpenGlVersion()
{
	return (char*)glGetString(GL_VERSION);
}