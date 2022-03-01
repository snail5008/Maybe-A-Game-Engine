#include "VAO.h"

Engine::VAO::VAO() {
	check(glGenVertexArrays(1, &m_VertexArray));
}

Engine::VAO::~VAO() {
	check(glDeleteVertexArrays(1, &m_VertexArray));
}

void Engine::VAO::Bind() {
	check(glBindVertexArray(m_VertexArray));
}

void Engine::VAO::Unbind() {
	check(glBindVertexArray(0));
}

void Engine::VAO::AddAttribute(int size, GLsizei stride, void* pointer) {
	check(glEnableVertexAttribArray(m_CurrentIndex));
	check(glVertexAttribPointer(m_CurrentIndex, size, GL_FLOAT, GL_FALSE, stride, pointer));
	m_CurrentIndex++;
}