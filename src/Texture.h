#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include "CheckOpenGLCalls.h"

namespace Engine {
	class Texture {
	private:
		GLuint m_Texture;
		unsigned char* m_Bytes;

	public:
		Texture(const char* image_path);

		void Bind();
		void Unbind();
	};
}