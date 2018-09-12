#pragma once
#include "../Rendering/Mesh.h"
#include "../Rendering/TextureAtlas.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Model.h"
#include "../Math/Random.h"
#include "../World/Chunks/Chunk.h"

class Game
{
public:
	Game();
	void Input();
	void Update();
	void Render();
private:
	std::vector<Model> models;
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
};

