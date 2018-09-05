#include "Game.h"
#include "../Game/Time.h"
#include "../Rendering/ResourceLoader.h"
#include "../../Globals.h"
#include <Input\Input.h>
#include <vector>
#include <stdio.h>



Game::Game()
	: shader("simpleShader.vert", "simpleShader.frag")
{
	// Set up shaders
	shader.AddUniform("clampFloat");
	shader.AddUniform("transform");
	shader.AddAttribute("offset");
	shader.AddAttribute("vOffset");

	// Load meshes
	cube = ResourceLoader::LoadMesh("cube.obj");

	// Set up chunk
	Model model;
	model.AddMesh(&cube);
	model.AddShader(&shader);

	int counter = 0;
	for (int z = 0; z < Globals::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < Globals::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < Globals::CHUNK_WIDTH; x++)
			{
				model.AddInstance(glm::vec3(x * 2.0f, y * 2.0f, z * 2.0f));
				counter++;
			}
		}
	}
	model.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	models.push_back(model);

	// Prepare Models
	for each(auto model in models) {
		model.Prepare();
	}

	// Set up camera projection
	camera.SetProjection(95, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0.001f, 1000.0f);
}

void Game::Input()
{
	if (Input::GetKey(GLFW_KEY_SPACE))
		camera.Move(glm::vec3(0, 1, 0), 0.005f);

	if (Input::GetKey(GLFW_KEY_LEFT_CONTROL))
		camera.Move(glm::vec3(0, 1, 0), -0.005f);

	if (Input::GetKey(GLFW_KEY_LEFT))
		camera.RotateY(-0.05f);

	if (Input::GetKey(GLFW_KEY_RIGHT))
		camera.RotateY(0.05f);

	if (Input::GetKey(GLFW_KEY_UP))
		camera.RotateX(-0.05f);

	if (Input::GetKey(GLFW_KEY_DOWN))
		camera.RotateX(0.05f);

	if (Input::GetKey(GLFW_KEY_W))
		camera.Move(glm::vec3(0, 0, 1), -0.005f);

	if (Input::GetKey(GLFW_KEY_S))
		camera.Move(glm::vec3(0, 0, 1), 0.005f);

	if (Input::GetKey(GLFW_KEY_A))
		camera.Move(glm::vec3(1, 0, 0), -0.005f);

	if (Input::GetKey(GLFW_KEY_D))
		camera.Move(glm::vec3(1, 0, 0), 0.005f);

	if (Input::GetMouseDown(GLFW_MOUSE_BUTTON_LEFT))
		printf("Left mouse button down\n");

	if (Input::GetMouseUp(GLFW_MOUSE_BUTTON_LEFT))
		printf("Left mouse button up\n");
}

void Game::Update()
{
	// Update shaders
	double delta = Time::GetDelta();
	clamp = (GLfloat)std::abs(std::sin(delta));

	shader.Bind();
	shader.SetUniformf("clampFloat", clamp);
	shader.UnBind();
}

void Game::Render()
{
	shader.Bind();
	for (int i = 0; i < models.size(); i++)
	{
		models[i].Draw(&camera);
	}
	shader.UnBind();
}