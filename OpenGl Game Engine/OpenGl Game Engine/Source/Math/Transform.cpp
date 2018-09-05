#include "Transform.h"
#include <glm\ext.hpp>
#include <glm\gtc\matrix_transform.hpp>

Transform::Transform()
{
	scale = glm::vec3(1, 1, 1);
	translation = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 s)
{
	scale = s;
	translation = pos;
	rotation = rot;
}

glm::mat4 Transform::GetTransformation()
{
	glm::mat4 matrix;

	matrix = glm::translate(matrix, translation);
	matrix = glm::scale(matrix, scale);

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	return matrix;
}

glm::vec3 Transform::GetTranslation()
{
	return translation;
}

void Transform::SetTranslation(glm::vec3 t)
{
	translation = t;
}

void Transform::SetTranslation(double x, double y, double z)
{
	translation.x = x;
	translation.y = y;
	translation.z = z;
}

glm::vec3 Transform::GetRotation()
{
	return rotation;
}

void Transform::SetRotation(glm::vec3 r)
{
	rotation = r;
}

void Transform::SetRotation(double x, double y, double z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}

void Transform::SetScale(glm::vec3 s)
{
	scale = s;
}

void Transform::SetScale(double x, double y, double z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}