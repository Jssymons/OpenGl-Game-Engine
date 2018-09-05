#pragma once
#include "../Modelling/Mesh.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Model.h"

class Game
{
public:
	Game();
	void Input();
	void Update();
	void Render();
private:
	std::vector<Model> models;
	Mesh m;
	Shader shader;
	GLfloat clamp = 0.0f;
	Camera camera;
};

