#include "VBO.h"

Engine::VBO::VBO() {
	check(glGenBuffers(1, &m_Buffer));
}

Engine::VBO::~VBO() {
	check(glDeleteBuffers(1, &m_Buffer));
}

void Engine::VBO::Bind() {
	check(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer));
}

void Engine::VBO::Unbind() {
	check(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Engine::VBO::SetData(void* data, int size, GLenum usage) {
	check(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}