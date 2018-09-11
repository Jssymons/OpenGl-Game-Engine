#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 vOffset;

out vec2 texCoord0;

uniform float clampFloat;
uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(vPosition + vOffset, 1.0);
	texCoord0 = texCoords;
}