#pragma once
#include "../Rendering/Mesh.h"
#include "../Rendering/TextureAtlas.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Model.h"
#include "../Math/Random.h"
#include "../World/World.h"

class Game
{
public:
	Game();
	void Input();
	void Update();
	void Render();
private:
	std::vector<Model> models;
	std::vector<Chunk> chunks;
	Mesh dirtMesh;
	Mesh grassMesh;
	Mesh stoneMesh;
	Mesh bedrockMesh;
	Mesh trunkMesh;
	Mesh leavesMesh;
	TextureAtlas atlas;
	Shader shader;
	GLfloat clamp = 0.0f;
	Camera camera;
	World world;
};

