#include "Window.h"
#include "Renderer.h"

#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"

#include "Mesh.h"

#include "Camera/Camera.h"
#include "Camera/FirstPersonController.h"

#include "InputOutput.h"

float quad[] = {
//       positions         tex coords
	 0.5f,  0.5f,  0.0f,   1.0f, 1.0f,  // 0 ^>
	 0.5f, -0.5f,  0.0f,   1.0f, 0.0f,  // 1 v>
	-0.5f, -0.5f,  0.0f,   0.0f, 0.0f,  // 2 <v
	-0.5f,  0.5f,  0.0f,   0.0f, 1.0f,  // 3 <^
};

unsigned int quad_indices[] = {
	0, 1, 2,
	3, 0, 2,
};

// learn opengl.com
float cube[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

bool ESCAPE_CURRENTLY_PRESSED = false;

int main() {
	Engine::Window Window(800, 600, "OpenGL");
	Engine::Renderer Renderer(&Window);
	Engine::Shader Shader;
	Engine::Mesh3D Mesh;
	Engine::Camera Camera(glm::vec3(0.0f));

	Shader.Compile(Engine::IO::ReadFile("res/shaders/default_vertex.glsl"), Engine::IO::ReadFile("res/shaders/default_fragment.glsl"));
	Shader.Use();

	Mesh.SetVertexData(cube, sizeof(cube), GL_STATIC_DRAW);
	Mesh.AddAttribute(3, 5 * sizeof(float), (void*)0);
	Mesh.AddAttribute(2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	Window.EnableVsync();


	Engine::Texture Texture("res/textures/stone.png", GL_RGB);
	Texture.Bind();

	Shader.SetUniform1i(Shader.GetUniformLocation("tex"), 0);

	Engine::FirstPersonController FPSController(&Camera, &Window, 45.0f, 0.1f, 100.0f, 0.1f);

	while (!Window.ShouldClose()) {

		Renderer.ClearColor(0, 0, 0);
		Renderer.DrawMesh3D(Mesh, 36);

		Window.Update();

		FPSController.UseShader(Shader, "transform");
		FPSController.Update();

		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_ESCAPE)) {
			if (!ESCAPE_CURRENTLY_PRESSED) {
				if (FPSController.CheckIfCaptured()) {
					FPSController.Uncapture();
				}
				else {
					Window.~Window();
					exit(0);
				}
			}
			ESCAPE_CURRENTLY_PRESSED = true;
		}
		else {
			ESCAPE_CURRENTLY_PRESSED = false;
		}
	}
}