#version 430 core

in vec2 texCoord0;

out vec4 fragColour;

uniform sampler2D textureSampler;

void main() {
	fragColour = texture(textureSampler, texCoord0);
}