#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 rot);
	void Move(glm::vec3 direction, double amount);
	void RotateX(double angle);
	void RotateY(double angle);
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetProjection(double fov, double width, double height, double zNear, double zFar);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
	static glm::vec3 yAxis;
	static double speed;
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::mat4 projection;
};

