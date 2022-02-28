#include "Renderer.h"

Engine::Renderer::Renderer(Window* window) {
	m_Window = window;
	glfwMakeContextCurrent(window->GetGLFWwindow());
	gladLoadGL();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

Engine::Renderer::~Renderer() {
	
}

void Engine::Renderer::ClearColor(float r, float g, float b) {
	check(glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f));
	check(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Engine::Renderer::DrawArrays(int count) {
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Engine::Renderer::DrawIndices(int count) {
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void Engine::Renderer::DrawMesh3D(Engine::Mesh3D& Mesh, int size) {
	Mesh.BindAll();
	if (Mesh.UsingIndices()) {
		DrawIndices(size);
	}
	else {
		DrawArrays(size);
	}
}


void Engine::Renderer::EnableWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Engine::Renderer::DisableWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}