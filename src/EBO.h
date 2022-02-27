#pragma once

#include <glad/glad.h>
#include "CheckOpenGLCalls.h"

namespace Engine {
	class EBO {
	private:
		GLuint m_Buffer;

	public:
		EBO();
		~EBO();

		void Bind();
		void Unbind();
		void SetData(void* data, int size, GLenum usage);
	};
}