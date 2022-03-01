#pragma once

#include "Window.h"
#include "Mesh.h"

#include <GLFW/glfw3.h>

#include "OpenGL/CheckOpenGLCalls.h"


namespace Engine {
	namespace Color {
		struct RGB;
		struct RGBA;
	}
	class Renderer {
	private:
		Window* m_Window;

	public:
		Renderer(Window*);
		~Renderer();

		void ClearColor(float, float, float);
		void DrawArrays(int count);
		void DrawIndices(int count);

		void DrawMesh3D(Engine::Mesh3D& Mesh, int size);

		void EnableWireframe();
		void DisableWireframe();
	};
}