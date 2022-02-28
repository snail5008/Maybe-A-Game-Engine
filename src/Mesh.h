#pragma once

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
	class Mesh3D {
	private:
		Engine::VAO VertexArrayObject;
		Engine::VBO VertexBufferObject;
		Engine::EBO ElementBufferObject;
		Engine::Shader ShaderProgram;

		int m_Size;
		bool m_UsingElementBuffer = false;
		int m_IndexCount = -1;

		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

	public:
		Mesh3D(float* vertices, int size, GLenum usage);
		Mesh3D();

		void AddAttribute(int size, GLsizei stride, void* pointer);
		void SetVertexData(float* vertices, int size, GLenum usage);
		void SetIndices(unsigned int* indices, int size, GLenum usage);
		void UnbindAll();
		void BindAll();

		void Scale(float x, float y, float z);
		void Translate(float x, float y, float z);

		int Size();

		bool UsingIndices();

		float* GetModelTransform();
	};
}