#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTextureCoords;

out vec3 colour;
out vec2 texture_coordinates;

void main() {
	colour = aColour;
	texture_coordinates = aTextureCoords;

	gl_Position.xyz = aPosition;
	gl_Position.w = 1.0f;
}