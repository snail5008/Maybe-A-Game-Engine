#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h" // include Window.h first
#include "Renderer.h"
#include "Shader.h"
#include "InputOutput.h"
#include "Mesh.h"
#include "Texture.h"

#include "Logger.h"
#include "Formatter.h"

int WIDTH = 800;
int HEIGHT = 600;
std::string TITLE = "OpenGL";

GLfloat triangle[] = {
/*       positions           colours       texture coords       */
	 0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // 0 ^>
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // 1 v>
	-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  // 2 <^
	-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // 3 <v
};

GLuint triangle_indices[] = {
	0, 1, 3,
	2, 0, 3
};

void LogDebugInfo() {
	Engine::Logger::Info(Engine::Format("OpenGL version: #c", (const char*)glGetString(GL_VERSION)));
}

int main() {
	Engine::Window Window(WIDTH, HEIGHT, TITLE);
	Engine::Renderer Renderer(&Window);
	Engine::Shader Shader;
	Engine::Mesh3D Mesh;

	Window.EnableVsync();

	Shader.Compile(Engine::IO::ReadFile("res/default_vertex.glsl"), Engine::IO::ReadFile("res/default_fragment.glsl"));
	Shader.Use();

	LogDebugInfo();

	Mesh.SetVertexData(triangle, sizeof(triangle), GL_STATIC_DRAW);
	Mesh.SetIndices(triangle_indices, sizeof(triangle_indices), GL_STATIC_DRAW);
	Mesh.AddAttribute(3, 8 * sizeof(GLfloat), (void*)0);
	Mesh.AddAttribute(3, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	Mesh.AddAttribute(2, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));

	Engine::Texture Texture("res/textures/shrek.png");
	Texture.Bind();

	GLuint texUniform = Shader.GetUniformLocation("tex");
	Shader.SetUniform1i(texUniform, 0);

	while (!Window.ShouldClose()) {
		Renderer.ClearColor(50, 50, 50);
		Renderer.DrawMesh3D(Mesh, 6);

		Window.Update();
	}

	return 0;
}