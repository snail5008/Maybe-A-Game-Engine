#version 460 core

out vec4 FragColour;
in vec3 colour;
in vec2 texture_coordinates;

uniform sampler2D tex;

void main() {
	FragColour = texture(tex, texture_coordinates);
	//FragColour *= vec3(1.0f, 0.0f, 0.0f);
}