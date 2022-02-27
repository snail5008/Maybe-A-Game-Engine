#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


namespace Engine {
	class Window {
	private:
		GLFWwindow* m_Window;

		int m_Width;
		int m_Height;
		double m_MouseX;
		double m_MouseY;

		static void ResizeCallback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}
		

	public:
		Window(int, int, std::string);
		~Window();

		GLFWwindow* GetGLFWwindow();

		int GetHeight();
		int GetWidth();
		int GetMouseX();
		int GetMouseY();
		double GetMouseXNormalised();
		double GetMouseYNormalised();

		bool ShouldClose();

		void PollEvents();
		void SwapBuffers();
		void EnableVsync();
		void UpdateSize();
		void UpdateMouseLocation();

		void Update();
	};
}