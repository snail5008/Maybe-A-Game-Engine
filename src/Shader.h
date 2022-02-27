#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>

#include "CheckOpenGLCalls.h"
#include "Logger.h"
#include "Formatter.h"

namespace Engine {
	class Shader {
	private:
		const char* m_VertexSource;
		const char* m_FragmentSource;

		GLuint m_VertexShader;
		GLuint m_FragmentShader;

		GLuint m_Program;

	public:
		Shader();
		Shader(std::string vertex_source, std::string fragment_source);
		~Shader();

		void Compile(std::string vertex_source, std::string fragment_source);
		void Use();
		
		int GetUniformLocation(const char* name);

		void SetUniform1f(int location, float data);
		void SetUniform1i(int location, float data);
	};
}