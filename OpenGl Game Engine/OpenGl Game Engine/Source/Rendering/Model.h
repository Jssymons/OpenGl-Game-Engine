#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "../Math/Transform.h"
#include "../World/Blocks/BlockType.h"

class Model
{
public:
	Model(BlockType type);
	void Prepare();
	void Draw(Camera* camera);
	void AddMesh(Mesh* mesh);
	void AddShader(Shader* shader);
	void AddTransformation(glm::vec3 pos, glm::vec3 rot, glm::vec3 s);
	void AddInstance(glm::vec3 offset);
	void RemoveInstance(glm::vec3 offset);
	void SetPosition(glm::vec3 pos);
	void SetPosition(double x, double y, double z);
	void SetRotation(glm::vec3 rot);
	void SetRotation(double x, double y, double z);
	void SetScale(glm::vec3 s);
	void SetScale(double x, double y, double z);
	bool HasInstances();
	BlockType GetBlockType();
private:
	std::vector<glm::vec3> instances;
	Transform transformation;
	Mesh* mesh;
	Shader* shader;
	BlockType blockType;
};

