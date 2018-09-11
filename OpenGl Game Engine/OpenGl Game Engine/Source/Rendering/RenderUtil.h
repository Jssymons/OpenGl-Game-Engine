#pragma once

#include <string>
class RenderUtil
{
public:
	static void ClearScreen();
	static void InitGraphics();
	static void SetTextures(bool enabled);
	static void SetWireframe(bool enabled);
	static char* GetOpenGlVersion();
};

