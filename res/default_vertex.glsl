#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 texture_coords;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 transform;

void main() {
	gl_Position = transform * model * vec4(aPosition, 1.0);
	texture_coords = aTexCoords;
}