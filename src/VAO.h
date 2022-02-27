#pragma once

#include <glad/glad.h>
#include "CheckOpenGLCalls.h"

namespace Engine {
	class VAO {
	private:
		GLuint m_VertexArray;
		int m_CurrentIndex = 0;

	public:
		VAO();
		~VAO();

		void Bind();
		void Unbind();

		/*
		 * @param size: The dimensions of the vertices (1, 2, 3, or 4)
		 * @param stride: The amount of vertices it takes to get to the next vertex
		 * @param pointer: The offset of the first value
		 */
		void AddAttribute(int size, GLsizei stride, void* pointer);
	};
}