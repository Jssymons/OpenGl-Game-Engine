#include "Model.h"

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

void Model::AddInstances(glm::vec3* offsets) {
	mesh->BufferInstances(offsets);
}

void Model::Draw(Camera* camera)
{
	shader->SetUniform("transform", camera->GetProjectionMatrix() * camera->GetViewMatrix() * transformation.GetTransformation());
	mesh->Draw();
}