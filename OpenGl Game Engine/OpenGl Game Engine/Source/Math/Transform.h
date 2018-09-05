#pragma once

#include <glm\glm.hpp>

class Transform
{
public:
	Transform();
	Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 s);
	glm::vec3 GetTranslation();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	glm::mat4 GetTransformation();
	void SetTranslation(glm::vec3 t);
	void SetTranslation(double x, double y, double z);
	void SetRotation(glm::vec3 t);
	void SetRotation(double x, double y, double z);
	void SetScale(glm::vec3 t);
	void SetScale(double x, double y, double z);
private:
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
};

