#include "Camera.h"

Engine::Camera::Camera(glm::vec3 pos) {
	Position = pos;
}

void Engine::Camera::SetMatrices(float fov, float near, float far, float w, float h, Shader& shader, const char* uniform) {
	m_FOV = fov;
	m_Near = near;
	m_Far = far;


	glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Projection = glm::mat4(1.0f);
	
	View = glm::lookAt(Position, Position + Direction, Up);
	Projection = glm::perspective(fov, (float)w / (float)h, near, far);

	shader.SetUniformMatrix4f(shader.GetUniformLocation(uniform), (float*)glm::value_ptr(Projection * View));
}

void Engine::Camera::RotateX(float amount) {
	Direction = glm::rotate(Direction, amount, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Engine::Camera::RotateY(float amount) {
	Direction = glm::rotate(Direction, amount, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Engine::Camera::RotateZ(float amount) {
	Direction = glm::rotate(Direction, amount, glm::vec3(0.0f, 0.0f, 1.0f));
}