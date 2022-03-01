#include "EBO.h"

Engine::EBO::EBO() {
	check(glGenBuffers(1, &m_Buffer));
}

Engine::EBO::~EBO() {
	check(glDeleteBuffers(1, &m_Buffer));
}

void Engine::EBO::Bind() {
	check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer));
}

void Engine::EBO::Unbind() {
	check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Engine::EBO::SetData(void* data, int size, GLenum usage) {
	check(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}