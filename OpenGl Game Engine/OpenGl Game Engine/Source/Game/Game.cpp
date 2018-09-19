#include "Game.h"
#include "../Game/Time.h"
#include "../Rendering/ResourceLoader.h"
#include "../Rendering//RenderUtil.h"
#include "../../Globals.h"
#include "../World/Blocks/BlockType.h"
#include "../World/World.h"
#include <Input\Input.h>
#include <vector>
#include <stdio.h>



Game::Game() : 
	shader("simpleShader.vert", "simpleShader.frag"),
	atlas("terrain.bmp", 256, 16)
{
	// Set up shaders
	shader.AddUniform("transform");
	shader.AddAttribute("vOffset");

	// Load meshes
	dirtMesh = ResourceLoader::CubePrimitive(atlas, BlockType::Dirt);
	grassMesh = ResourceLoader::CubePrimitive(atlas, BlockType::Grass);
	bedrockMesh = ResourceLoader::CubePrimitive(atlas, BlockType::Bedrock);
	stoneMesh = ResourceLoader::CubePrimitive(atlas, BlockType::Stone);
	trunkMesh = ResourceLoader::CubePrimitive(atlas, BlockType::Trunk);
	leavesMesh = ResourceLoader::CubePrimitive(atlas, BlockType::Leaves);

	// Set up models
	Model air(BlockType::None);

	Model dirt(BlockType::Dirt);
	dirt.AddMesh(&dirtMesh);
	dirt.AddShader(&shader);
	dirt.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model grass(BlockType::Grass);
	grass.AddMesh(&grassMesh);
	grass.AddShader(&shader);
	grass.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model stone(BlockType::Bedrock);
	stone.AddMesh(&stoneMesh);
	stone.AddShader(&shader);
	stone.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model bedrock(BlockType::Stone);
	bedrock.AddMesh(&bedrockMesh);
	bedrock.AddShader(&shader);
	bedrock.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model trunk(BlockType::Trunk);
	trunk.AddMesh(&trunkMesh);
	trunk.AddShader(&shader);
	trunk.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model leaves(BlockType::Leaves);
	leaves.AddMesh(&leavesMesh);
	leaves.AddShader(&shader);
	leaves.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	models.push_back(air);
	models.push_back(dirt);
	models.push_back(grass);
	models.push_back(stone);
	models.push_back(bedrock);
	models.push_back(trunk);
	models.push_back(leaves);

	world.Create(&models);

	// Prepare Models
	for each(auto model in models) {
		if (model.HasInstances())
		{
			if (model.GetBlockType() != BlockType::None)
			{
				model.Prepare();
			}
		}
	}

	// Set up camera projection
	camera.SetProjection(95, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0.001f, 1000.0f);
}

void Game::Input()
{
	Input::Update(&camera, &world);

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

	if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
		camera.Move(glm::vec3(0, 0, 1), -0.0500f);

	if (Input::GetKey(GLFW_KEY_LEFT_CONTROL))
		camera.Move(glm::vec3(0, 0, 1), 0.0500f);

	if (Input::GetMouseDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		printf("Left mouse button down\n");
	}

	if (Input::GetMouseUp(GLFW_MOUSE_BUTTON_LEFT))
	{
		printf("Left mouse button up\n");
		Block* currentBlock = Input::GetCurrentBlock();

		if (currentBlock)
		{
			BlockType type = currentBlock->GetBlockType();
			models[type].RemoveInstance(currentBlock->GetPosition());
			models[type].Prepare();
		}
	}

	if (Input::GetKey(GLFW_KEY_F1)) 
	{
		printf("Toggling wireframe on\n");
		RenderUtil::SetWireframe(true);
	}

	if (Input::GetKey(GLFW_KEY_F2)) 
	{
		printf("Toggling wireframe off\n");
		RenderUtil::SetWireframe(false);
	}
}

void Game::Update()
{
	// Update shaders
	double delta = Time::GetDelta();
}

void Game::Render()
{
	shader.Bind();
	atlas.texture.Bind();
	for (int i = 0; i < models.size(); i++)
	{
		if (models[i].HasInstances() && models[i].GetBlockType() != BlockType::None)
		{
			models[i].Draw(&camera);
		}
	}
	shader.UnBind();
}