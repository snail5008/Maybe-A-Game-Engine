#version 460 core

out vec4 FragColour;

in vec2 texture_coords;

uniform sampler2D tex;

void main() {
	FragColour = texture(tex, texture_coords);//vec4(1.0f, 0.0f, 1.0f, 1.0f);
}