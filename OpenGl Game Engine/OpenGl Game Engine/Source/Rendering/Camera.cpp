#include "Camera.h"
#include "../Input/Input.h"
#include "../Game/Time.h"
#include "../../Globals.h"
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 Camera::yAxis = glm::vec3(0, 1, 0);
double Camera::speed = 0.5f;

Camera::Camera()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0); 
	projection = glm::perspective(glm::radians(95.0f), Globals::SCREEN_WIDTH / Globals::SCREEN_HEIGHT, 0.001f, 1000.0f);
}

Camera::Camera(glm::vec3 pos, glm::vec3 rot)
{
	position = pos;
	rotation = rot;
}

void Camera::Move(glm::vec3 direction, double amount)
{
	glm::vec4 input = glm::vec4(direction *= amount, 1.0f);
	position += glm::vec3(input * GetViewMatrix());
}

void Camera::RotateX(double angle)
{
	rotation.x += angle;
}

void Camera::RotateY(double angle)
{
	rotation.y += angle;
}

void Camera::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void Camera::SetRotation(glm::vec3 rot)
{
	rotation = rot;
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

glm::vec3 Camera::GetRotation()
{
	return rotation;
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 matrix;

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -position);

	return matrix;
}

void Camera::SetProjection(double fov, double width, double height, double zNear, double zFar)
{
	projection = glm::perspective(glm::radians(fov), width / height, zNear, zFar);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projection;
}
