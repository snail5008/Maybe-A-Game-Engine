#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#include "InputOutput.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float quad[] = {
	 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // 0 ^>
	 0.5f, -0.5f, 0.5f,  1.0f, 0.0f,  // 1 v>
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // 2 <v
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  // 3 <^
};

unsigned int quad_indices[] = {
	0, 1, 2,
	3, 0, 2,
};

int main() {
	Engine::Window Window(800, 600, "OpenGL");
	Engine::Renderer Renderer(&Window);
	Engine::Shader Shader;
	Engine::Mesh3D Mesh;
	
	Shader.Compile(Engine::IO::ReadFile("res/default_vertex.glsl"), Engine::IO::ReadFile("res/default_fragment.glsl"));
	Shader.Use();

	Mesh.SetVertexData(quad, sizeof(quad), GL_STATIC_DRAW);
	Mesh.SetIndices(quad_indices, sizeof(quad_indices), GL_STATIC_DRAW);
	Mesh.AddAttribute(3, 5 * sizeof(float), (void*)0);
	Mesh.AddAttribute(2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glm::mat4 Model = glm::mat4(1.0f);
	//glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Projection = glm::mat4(1.0f);

	Window.EnableVsync();

	int ModelLocation = Shader.GetUniformLocation("model");
	int ViewLocation = Shader.GetUniformLocation("view");
	int ProjectionLocation = Shader.GetUniformLocation("projection");

	Engine::Texture Texture("res/textures/shrek.png");
	Texture.Bind();

	int TexUniform = Shader.GetUniformLocation("tex");
	Shader.SetUniform1i(TexUniform, 0);

	while (!Window.ShouldClose()) {
		Renderer.ClearColor(50, 50, 50);
		Renderer.DrawMesh3D(Mesh, 6);

		//View = glm::translate(View, glm::vec3(0.0f, 0.5f, 1.0f));
		//Model = glm::rotate(Model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		Projection = glm::perspective(glm::radians(90.0f), 800.0f/600.0f, 0.1f, 1000.0f);

		Engine::Logger::Info(Engine::Format("glfwGetTime(): #f", glfwGetTime()));
		Model = glm::rotate(Model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));


		Shader.SetUniformMatrix4f(ModelLocation, glm::value_ptr(Model));
		//Shader.SetUniformMatrix4f(ViewLocation, glm::value_ptr(View));
		Shader.SetUniformMatrix4f(ProjectionLocation, glm::value_ptr(Projection));

		Window.Update();
	}
}