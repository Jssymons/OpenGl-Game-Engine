#pragma once
#include <GL\glfw3.h>
#include <glm\vec2.hpp>
#include "../Rendering/Camera.h"
#include "../World/World.h"
#include "../World/Blocks/Block.h"

class Input
{
public:
	static void SetWindow(GLFWwindow* displayWindow);
	static void Update(Camera* camera, World* world);
	static bool GetKey(int keyCode);
	static bool GetKeyDown(int keyCode);
	static bool GetKeyUp(int keyCode);
	static glm::vec2 GetMousePos();
	static glm::vec3 GetMouseDirection();
	static Block* GetCurrentBlock();
	static bool GetMouse(int mouseButton);
	static bool GetMouseUp(int mouseButton);
	static bool GetMouseDown(int mouseButton);
	static const int NUM_KEYCODES = 256;
	static const int NUM_MOUSECODES = 7;
	static const float mouseX;
	static const float mouseY;
private:
	static void UpdateMouse(Camera* camera, World* world);
	static void RotateCamera(Camera* camera, double x, double y);
	static GLFWwindow* window;
	static glm::vec3 mouseDirection;
	static bool currentKeys[NUM_KEYCODES];
	static bool downKeys[NUM_KEYCODES];
	static bool upKeys[NUM_KEYCODES];
	static bool currentMouse[NUM_MOUSECODES];
	static bool downMouse[NUM_MOUSECODES];
	static bool upMouse[NUM_MOUSECODES];
	static Block* currentBlock;
	static glm::vec3 CalculateMouseRay(Camera* camera);
	static Block* GetSelectedBlock(glm::vec3 ray, World* world, Camera* camera);
};

