#include "Application.h"
#include "../Game/Time.h"
#include "../../Globals.h"
#include "../World/Blocks/Block.h"
#include <glm\ext.hpp>
#include <GL\glfw3.h>
#include <thread>

Application::Application()
{
	GLFWwindow* window = display.CreateWindow(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, WINDOW_TITLE);
	Input::SetWindow(window);
	isRunning = false;
	RenderUtil::InitGraphics();
	printf("OpenGL Version: %s\n", RenderUtil::GetOpenGlVersion());
}

void Application::Start()
{
	game = new Game();
	if (isRunning)
		return;
	Run();
}

void Application::Stop()
{
	if (!isRunning)
		return;

	isRunning = false;
}

void Application::Run()
{
	isRunning = true;

	double refreshRate = 1.0 / 5000.0; // How long a frame should take in milliseconds
	double framerateTimer = 0.0;
	double framerateCounter = 0.0;
	double lastTime = 0.0;
	double currentTime = glfwGetTime();

	while (isRunning)
	{
		bool shouldRender = false;

		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		framerateTimer += frameTime;

		while (frameTime > refreshRate)
		{
			shouldRender = true;
			frameTime -= refreshRate;

			Time::SetDelta(refreshRate);

			// Do input
			game->Input();

			// Do calculation
			game->Update();

			if (display.WindowShouldClose() && display.CheckKeyPress(GLFW_KEY_ESCAPE))
				Stop();

			if (framerateTimer > 1)
			{
				printf("FPS: %f\n", framerateCounter);
				framerateTimer = 0.0;
				framerateCounter = 0.0;

				printf("Mouse direction %s\n", glm::to_string(Input::GetMouseDirection()).c_str());

				Block* block = Input::GetCurrentBlock();
				if (block)
				{
					printf("Block type %d selected at position (%s)", block->GetBlockType(), glm::to_string(block->GetPosition()).c_str());
				}

				printf("\n");
			}
		}

		if (shouldRender)
		{
			Render();
			framerateCounter++;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	CleanUp();
}

void Application::Render()
{
	RenderUtil::ClearScreen();
	game->Render();
	display.Render();
}

void Application::CleanUp()
{
	display.Dispose();
}