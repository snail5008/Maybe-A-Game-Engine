#pragma once

#include <glad/glad.h>
#include "CheckOpenGLCalls.h"

namespace Engine {
	class VBO {
	private:
		GLuint m_Buffer;

	public:
		VBO();
		~VBO();

		void Bind();
		void Unbind();
		void SetData(void* data, int size, GLenum usage);
	};
}