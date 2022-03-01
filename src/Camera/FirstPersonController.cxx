#include "FirstPersonController.h"

Engine::FirstPersonController::FirstPersonController(Engine::Camera* C, Engine::Window* W, float FOVdegrees, float near, float far, float sensitivity) {
	m_Camera = C;
	m_Window = W;

	m_FOV = FOVdegrees;
	m_Near = near;
	m_Far = far;
	m_Sensitivity = sensitivity;
}
void Engine::FirstPersonController::UseShader(Engine::Shader& S, const char* uniform_name) {
	m_Camera->UseShader(S, uniform_name);
}
void Engine::FirstPersonController::Update() {
	m_Camera->SetMatrices(glm::radians(m_FOV), m_Near, m_Far, m_Window->GetWidth(), m_Window->GetHeight());

	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_J) == GLFW_PRESS) {
		m_FOV -= 0.5f;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_K) == GLFW_PRESS) {
		m_FOV += 0.5f;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_L) == GLFW_PRESS) {
		m_FOV = 45.0f;
	}

	if (m_IsCaptured) {
		// shamelessly copied and pased from learnopengl.com lol
		yaw += (float)(m_Window->GetMouseX() - OldMouseX) * m_Sensitivity;
		pitch -= (float)(m_Window->GetMouseY() - OldMouseY) * m_Sensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		m_Camera->Direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		m_Camera->Direction.y = sin(glm::radians(pitch));
		m_Camera->Direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		OldMouseX = m_Window->GetMouseX();
		OldMouseY = m_Window->GetMouseY();
	}



	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS) {
		m_Camera->Position += m_Camera->Direction * speed;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS) {
		m_Camera->Position += m_Camera->Direction * -speed;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS) {
		m_Camera->Position += glm::normalize(glm::cross(m_Camera->Direction, m_Camera->Up)) * -speed;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS) {
		m_Camera->Position += glm::normalize(glm::cross(m_Camera->Direction, m_Camera->Up)) * speed;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		m_Camera->Position.y -= speed;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_Camera->Position.y += speed;
	}
	if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		speed = 0.5f;
	}
	else {
		speed = 0.05f;
	}

	int state = glfwGetMouseButton(m_Window->GetGLFWwindow(), GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		m_Window->CaptureMouse();
		m_IsCaptured = true;
	}

}

bool Engine::FirstPersonController::CheckIfCaptured() {
	return m_IsCaptured;
}

void Engine::FirstPersonController::Capture() {
	m_Window->CaptureMouse();
	m_IsCaptured = true;
}
void Engine::FirstPersonController::Uncapture() {
	m_Window->UncaptureMouse();
	m_IsCaptured = false;
}