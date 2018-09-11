#include "Game.h"
#include "../Game/Time.h"
#include "../Rendering/ResourceLoader.h"
#include "../Rendering//RenderUtil.h"
#include "../../Globals.h"
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
	dirtMesh = ResourceLoader::CubePrimitive(atlas, Globals::BLOCK_TYPES::Dirt);
	grassMesh = ResourceLoader::CubePrimitive(atlas, Globals::BLOCK_TYPES::Grass);
	bedrockMesh = ResourceLoader::CubePrimitive(atlas, Globals::BLOCK_TYPES::Bedrock);
	stoneMesh = ResourceLoader::CubePrimitive(atlas, Globals::BLOCK_TYPES::Stone);
	trunkMesh = ResourceLoader::CubePrimitive(atlas, Globals::BLOCK_TYPES::Trunk);
	leavesMesh = ResourceLoader::CubePrimitive(atlas, Globals::BLOCK_TYPES::Leaves);

	// Set up models
	Model dirt;
	dirt.AddMesh(&dirtMesh);
	dirt.AddShader(&shader);
	dirt.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model grass;
	grass.AddMesh(&grassMesh);
	grass.AddShader(&shader);
	grass.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model stone;
	stone.AddMesh(&stoneMesh);
	stone.AddShader(&shader);
	stone.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model bedrock;
	bedrock.AddMesh(&bedrockMesh);
	bedrock.AddShader(&shader);
	bedrock.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model trunk;
	trunk.AddMesh(&trunkMesh);
	trunk.AddShader(&shader);
	trunk.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Model leaves;
	leaves.AddMesh(&leavesMesh);
	leaves.AddShader(&shader);
	leaves.AddTransformation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));


	// Build chunk
	int counter = 0;
	for (int z = 0; z < Globals::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < Globals::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < Globals::CHUNK_WIDTH; x++)
			{
				if (z > 0 && z < Globals::CHUNK_WIDTH - 1
					&& x > 0 && x < Globals::CHUNK_WIDTH - 1
					&& y > 0 && y < Globals::CHUNK_HEIGHT - 1)
				{
					continue;
				}

				glm::vec3 currentPos = glm::vec3(x * 2.0f, y * 2.0f, z * 2.0f);

				if (y == Globals::CHUNK_HEIGHT - 1)
				{
					grass.AddInstance(currentPos);
				}
				else if (y > (Globals::CHUNK_HEIGHT / 3) * 2)
				{
					dirt.AddInstance(currentPos);
				}
				else if (y > (Globals::CHUNK_HEIGHT / 3 + Globals::CHUNK_HEIGHT / 8))
				{
					if (random.IntInRange(0, 4) == 0)
					{
						stone.AddInstance(currentPos);
					}
					else
					{
						dirt.AddInstance(currentPos);
					}
				}
				else if (y > Globals::CHUNK_HEIGHT / 3)
				{
					if (random.IntInRange(0, 1) == 0)
					{
						stone.AddInstance(currentPos);
					}
					else
					{
						dirt.AddInstance(currentPos);
					}
				}
				else if (y > 2)
				{
					stone.AddInstance(currentPos);
				}
				else
				{
					bedrock.AddInstance(currentPos);
				}

				counter++;
			}
		}
	}

	// Create trees
	int baseTerrainHeight = Globals::CHUNK_HEIGHT;
	for (int z = 0; z < Globals::CHUNK_WIDTH; z = z + 4)
	{
		for (int x = 0; x < Globals::CHUNK_WIDTH; x = x + 4)
		{
			if (random.IntInRange(0, 6) == 0)
			{
				// Trunk
				int trunkHeight = random.IntInRange(4, 10);
				for (int i = 0; i < trunkHeight; i++) 
				{
					trunk.AddInstance(glm::vec3(x * 2.0f, (baseTerrainHeight + i) * 2.0f, z * 2.0f));
				}

				// Leaves
				int foliageWidth = (random.IntInRange(1, 2) * 2) + 1;
				int foliageBottom = baseTerrainHeight + trunkHeight - 1;
				int foliageHeight = random.IntInRange(3, 4);

				for (int ly = 0; ly < foliageHeight; ly++) 
				{
					for (int lx = x - (foliageWidth - ly); lx < x + (foliageWidth - ly); lx++)
					{
						for (int lz = z - (foliageWidth - ly); lz < z + (foliageWidth - ly); lz++)
						{
							leaves.AddInstance(glm::vec3(lx * 2.0f, (ly + foliageBottom) * 2.0f, lz * 2.0f));
						}
					}
				}

			}
		}
	}


	models.push_back(dirt);
	models.push_back(grass);
	models.push_back(stone);
	models.push_back(bedrock);
	models.push_back(trunk);
	models.push_back(leaves);

	// Prepare Models
	for each(auto model in models) {
		if (model.HasInstances())
		{
			model.Prepare();
		}
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

	if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
		camera.Move(glm::vec3(0, 0, 1), -0.0500f);

	if (Input::GetMouseDown(GLFW_MOUSE_BUTTON_LEFT))
		printf("Left mouse button down\n");

	if (Input::GetMouseUp(GLFW_MOUSE_BUTTON_LEFT))
		printf("Left mouse button up\n");

	if (Input::GetKey(GLFW_KEY_F1)) {
		printf("Toggling wireframe on\n");
		RenderUtil::SetWireframe(true);
	}

	if (Input::GetKey(GLFW_KEY_F2)) {
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
		if (models[i].HasInstances())
		{
			models[i].Draw(&camera);
		}
	}
	shader.UnBind();
}