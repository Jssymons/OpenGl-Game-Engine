#pragma once
#include <Display\Display.h>
#include <Input\Input.h>
#include <World\Blocks\Block.h>
#include <Game\Game.h>
#include <Rendering\RenderUtil.h>
#include <string>

class Application
{
public:
	Application();
	void Start();
	void Stop();
	void Run();
	void Render();
	void CleanUp();
private:
	bool isRunning;
	const std::string WINDOW_TITLE = "OpenGL Game Engine";
	Display display;
	Input input;
	Game* game;
};

