#include "Shader.h"

Engine::Shader::Shader() : m_FragmentShader(0), m_VertexShader(0), m_Program(0), m_FragmentSource("#error no fragment shader supplied"), m_VertexSource("#error no vertex shader supplied") {
	
}

Engine::Shader::Shader(std::string vertex_source, std::string fragment_source) {
	Compile(vertex_source, fragment_source);
}

Engine::Shader::~Shader() {
	check(glDeleteProgram(m_Program));
}

void Engine::Shader::Compile(std::string vertex_source, std::string fragment_source) {
	m_VertexSource = vertex_source.c_str();
	m_FragmentSource = fragment_source.c_str();

	check(m_VertexShader = glCreateShader(GL_VERTEX_SHADER));
	check(m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
	check(m_Program = glCreateProgram());

	check(glShaderSource(m_VertexShader, 1, &m_VertexSource, nullptr));
	check(glShaderSource(m_FragmentShader, 1, &m_FragmentSource, nullptr));

	check(glCompileShader(m_VertexShader));
	check(glCompileShader(m_FragmentShader));

	check(glAttachShader(m_Program, m_VertexShader));
	check(glAttachShader(m_Program, m_FragmentShader));

	check(glLinkProgram(m_Program));

	int Success;
	char InfoLog[512];
	check(glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &Success));
	if (!Success) {
		check(glGetShaderInfoLog(m_VertexShader, 512, nullptr, InfoLog));
		Logger::Error(Engine::Format("Could not compile vertex shader: #c", InfoLog));
	}

	Success = true;
	check(glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &Success));
	if (!Success) {
		check(glGetShaderInfoLog(m_FragmentShader, 512, nullptr, InfoLog));
		Logger::Error(Engine::Format("Could not compile fragment shader: #c", InfoLog));
	}

	Success = true;
	check(glGetProgramiv(m_Program, GL_LINK_STATUS, &Success));
	if (!Success) {
		check(glGetProgramInfoLog(m_Program, 512, nullptr, InfoLog));
		Logger::Error(Engine::Format("Could not link program: #c", InfoLog));
	}

	check(glDetachShader(m_Program, m_VertexShader));
	check(glDetachShader(m_Program, m_FragmentShader));

	check(glDeleteShader(m_VertexShader));
	check(glDeleteShader(m_FragmentShader));
}

void Engine::Shader::Use() {
	check(glUseProgram(m_Program));
}

int Engine::Shader::GetUniformLocation(const char* name) {
	check(int ret = glGetUniformLocation(m_Program, name));
	return ret;
}

void Engine::Shader::SetUniform1f(int location, float data) {
	check(glUniform1f(location, data));
}

void Engine::Shader::SetUniform1i(int location, float data) {
	check(glUniform1i(location, data));
}

void Engine::Shader::SetUniformMatrix4f(int location, float* data) {
	check(glUniformMatrix4fv(location, 1, GL_FALSE, data));
}