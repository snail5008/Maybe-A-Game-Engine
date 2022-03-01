#version 460 core

out vec4 FragColour;

in vec2 texture_coords;

uniform sampler2D tex;

void main() {
	vec4 image = texture(tex, texture_coords);
	FragColour = image;
}