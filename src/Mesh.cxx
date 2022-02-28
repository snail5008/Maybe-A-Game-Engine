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


void Engine::Mesh3D::Scale(float x, float y, float z) {
	m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(x, y, z));
}

void Engine::Mesh3D::Translate(float x, float y, float z) {
	m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(x, y, z));
}


int Engine::Mesh3D::Size() {
	return m_Size;
}

bool Engine::Mesh3D::UsingIndices() {
	return m_UsingElementBuffer;
}

float* Engine::Mesh3D::GetModelTransform() {
	return glm::value_ptr(m_ModelMatrix);
}