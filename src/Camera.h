#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

namespace Engine {
	class Camera {
	private:
		float m_FOV;
		float m_Near;
		float m_Far;
		
	public:
		glm::vec3 Position;
		glm::vec3 Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		int Width;
		int Height;

		Camera(glm::vec3 pos);

		void SetMatrices(float fov, float near, float far, float w, float h, Shader& shader, const char* uniform);
	};
}