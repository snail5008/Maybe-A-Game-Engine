#pragma once

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

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

	public:
		Mesh3D(float* vertices, int size, GLenum usage);
		Mesh3D();

		void AddAttribute(int size, GLsizei stride, void* pointer);
		void SetVertexData(float* vertices, int size, GLenum usage);
		void SetIndices(unsigned int* indices, int size, GLenum usage);
		void UnbindAll();
		void BindAll();

		int Size();

		bool UsingIndices();
	};
}