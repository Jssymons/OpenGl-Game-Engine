#include "Model.h"

Model::Model(BlockType type)
{
	blockType = type;
}

void Model::AddMesh(Mesh* m)
{
	mesh = m;
}

void Model::AddShader(Shader * s)
{
	shader = s;
}

void Model::AddTransformation(glm::vec3 pos, glm::vec3 rot, glm::vec3 s)
{
	transformation = Transform(pos, rot, s);
}

void Model::SetPosition(glm::vec3 pos)
{
	transformation.SetTranslation(pos);
}

void Model::SetPosition(double x, double y, double z)
{
	transformation.SetTranslation(x, y, z);
}

void Model::SetRotation(glm::vec3 rot)
{
	transformation.SetRotation(rot);
}

void Model::SetRotation(double x, double y, double z)
{
	transformation.SetRotation(x, y, z);
}

void Model::SetScale(glm::vec3 s)
{
	transformation.SetScale(s);
}

void Model::SetScale(double x, double y, double z)
{
	transformation.SetScale(x, y, z);
}

void Model::AddInstance(glm::vec3 offset) {
	instances.push_back(offset);
}

void Model::RemoveInstance(glm::vec3 removeOffset)
{
	std::vector<glm::vec3> newInstances;
	for each (auto offset in instances)
	{
		if (offset != removeOffset)
		{
			newInstances.push_back(offset);
		}
	}

	instances = newInstances;
}

void Model::Prepare() {
	mesh->BufferInstances(instances);
}

void Model::Draw(Camera* camera)
{
	shader->SetUniform("transform", camera->GetProjectionMatrix() * camera->GetViewMatrix() * transformation.GetTransformation());
	mesh->Draw(instances.size());
}

bool Model::HasInstances()
{
	return instances.size() != 0;
}

BlockType Model::GetBlockType()
{
	return blockType;
}