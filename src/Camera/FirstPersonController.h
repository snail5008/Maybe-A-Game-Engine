#pragma once

#include "../Window.h"
#include "../OpenGL/Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// THIS IS A DEBUG CHARACTER CONTROLLER; USE ONLY FOR TESTING

namespace Engine {
	class FirstPersonController {
	private:
		Engine::Camera* m_Camera;
		Engine::Window* m_Window;

		float yaw = 0.0f;
		float pitch = 0.0f;
		float speed = 0.05f;
		double OldMouseX = 0.0;
		double OldMouseY = 0.0;

		bool m_IsCaptured = false;

		float m_FOV;
		float m_Near;
		float m_Far;
		float m_Sensitivity;

	public:
		FirstPersonController(Engine::Camera* C, Engine::Window* W, float FOVdegrees, float near, float far, float sensitivity);
		void UseShader(Engine::Shader& S, const char* uniform_name);
		void Update();
		bool CheckIfCaptured();
		void Capture();
		void Uncapture();

		Engine::Camera* GetCamera();
	};
}