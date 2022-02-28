#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

#include "InputOutput.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

bool IS_CAPTURED = true;
bool ESCAPE_CURRENTLY_PRESSED = false;
float SENSITIVITY = 0.1f;

float FOV = 45.0f;

int main() {
	Engine::Window Window(800, 600, "OpenGL");
	Engine::Renderer Renderer(&Window);
	Engine::Shader Shader;
	Engine::Mesh3D Mesh;
	Engine::Camera Camera(glm::vec3(0.0f, 0.0f, 2.0f));

	Shader.Compile(Engine::IO::ReadFile("res/default_vertex.glsl"), Engine::IO::ReadFile("res/default_fragment.glsl"));
	Shader.Use();

	Mesh.SetVertexData(cube, sizeof(cube), GL_STATIC_DRAW);
	//Mesh.SetIndices(quad_indices, sizeof(quad_indices), GL_STATIC_DRAW);
	Mesh.AddAttribute(3, 5 * sizeof(float), (void*)0);
	Mesh.AddAttribute(2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	Mesh.Translate(0.0f, 0.5f, 0.0f);
	Mesh.Scale(1.0f, 1.0f, 1.0f);

	Window.EnableVsync();


	Engine::Texture Texture("res/textures/stone.png");
	Texture.Bind();

	int ModelLocation = Shader.GetUniformLocation("model");
	int TexUniform = Shader.GetUniformLocation("tex");
	Shader.SetUniform1i(TexUniform, 0);


	double OldMouseX = Window.GetMouseX();
	double OldMouseY = Window.GetMouseY();
	float yaw = 0.0f;
	float pitch = 0.0f;
	while (!Window.ShouldClose()) {

		OldMouseX = Window.GetMouseX();
		OldMouseY = Window.GetMouseY();

		Renderer.ClearColor(50, 50, 50);
		Renderer.DrawMesh3D(Mesh, 36);

		Camera.SetMatrices(glm::radians(FOV), 0.1f, 100.0f, Window.GetWidth(), Window.GetHeight(), Shader, "transform");

		Shader.SetUniformMatrix4f(ModelLocation, Mesh.GetModelTransform());

		Window.Update();

		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_J) == GLFW_PRESS) {
			FOV -= 0.5f;
		}
		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_K) == GLFW_PRESS) {
			FOV += 0.5f;
		}
		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_L) == GLFW_PRESS) {
			FOV = 45.0f;
		}

		if (IS_CAPTURED) {
			// shamelessly copied and pased from learnopengl.com
			yaw += (float)(Window.GetMouseX() - OldMouseX) * SENSITIVITY;
			pitch += (float)(Window.GetMouseY() - OldMouseY) * SENSITIVITY;

			Camera.Direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			Camera.Direction.y = sin(glm::radians(pitch));
			Camera.Direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		}


		float speed = 0.05f;
		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS) {
			Camera.Position += Camera.Direction * speed;
		}
		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS) {
			Camera.Position += Camera.Direction * -speed;
		}
		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS) {
			Camera.Position += glm::normalize(glm::cross(Camera.Direction, Camera.Up)) * -speed;
		}
		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS) {
			Camera.Position += glm::normalize(glm::cross(Camera.Direction, Camera.Up)) * speed;
		}

		int state = glfwGetMouseButton(Window.GetGLFWwindow(), GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS)
		{
			Window.CaptureMouse();
			IS_CAPTURED = true;
		}

		if (glfwGetKey(Window.GetGLFWwindow(), GLFW_KEY_ESCAPE)) {
			if (!ESCAPE_CURRENTLY_PRESSED) {
				if (IS_CAPTURED) {
					Window.UncaptureMouse();
					IS_CAPTURED = false;
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