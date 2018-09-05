#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 offset;
layout(location = 2) in vec3 vOffset;

out vec4 colour;

uniform float clampFloat;
uniform mat4 transform;

void main()
{
	colour = vec4(clamp(vPosition, 0.0, clampFloat), 1.0);
	gl_Position = transform * vec4(vPosition + vOffset, 1.0);
}