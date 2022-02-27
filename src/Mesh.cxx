#include "Mesh.h"

Engine::Mesh3D::Mesh3D(float* vertices, int size, GLenum usage) {
	SetVertexData(vertices, size, usage);
}

Engine::Mesh3D::Mesh3D() : m_Size(0) {

}

void Engine::Mesh3D::SetVertexData(float* vertices, int size, GLenum usage) {
	VertexBufferObject.Bind();
	VertexArrayObject.Bind();
	VertexBufferObject.SetData(vertices, size, usage);
	m_Size = size;
}

void Engine::Mesh3D::SetIndices(unsigned int* indices, int size, GLenum usage) {
	ElementBufferObject.Bind();
	ElementBufferObject.SetData(indices, size, usage);
	m_UsingElementBuffer = true;
}

void Engine::Mesh3D::AddAttribute(int size, GLsizei stride, void* pointer) {
	VertexArrayObject.Bind();
	VertexArrayObject.AddAttribute(size, stride, pointer);
}

void Engine::Mesh3D::UnbindAll() {
	if (m_UsingElementBuffer)
		ElementBufferObject.Unbind();

	VertexArrayObject.Unbind();
	VertexBufferObject.Unbind();
}

void Engine::Mesh3D::BindAll() {
	if (m_UsingElementBuffer)
		ElementBufferObject.Bind();

	VertexArrayObject.Bind();
	VertexBufferObject.Bind();
}

int Engine::Mesh3D::Size() {
	return m_Size;
}

bool Engine::Mesh3D::UsingIndices() {
	return m_UsingElementBuffer;
}