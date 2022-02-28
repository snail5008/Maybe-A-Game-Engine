#include "Window.h"

Engine::Window::Window(int width, int height, std::string title, int samples) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, samples);
	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	
	m_Width = width;
	m_Height = height;

	m_MouseX = 0;
	m_MouseY = 0;

	glfwSetWindowSizeCallback(m_Window, ResizeCallback);
}

Engine::Window::~Window() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

GLFWwindow* Engine::Window::GetGLFWwindow() {
	return m_Window;
}

int Engine::Window::GetHeight() {
	return m_Height;
}

int Engine::Window::GetWidth() {
	UpdateMouseLocation();
	return m_Width;
}

int Engine::Window::GetMouseX() {
	UpdateMouseLocation();
	return (int)m_MouseX;
}

int Engine::Window::GetMouseY() {
	UpdateMouseLocation();
	return (int)m_MouseY;
}

double Engine::Window::GetMouseXNormalised() {
	return ((double)GetMouseX())/((double)m_Width);
}

double Engine::Window::GetMouseYNormalised() {
	return ((double)GetMouseY()) / ((double)m_Height);
}

bool Engine::Window::ShouldClose() {
	return glfwWindowShouldClose(m_Window);
}

void Engine::Window::PollEvents() {
	glfwPollEvents();
}

void Engine::Window::SwapBuffers() {
	glfwSwapBuffers(m_Window);
}

void Engine::Window::EnableVsync() {
	glfwSwapInterval(1);
}

void Engine::Window::UpdateSize() {
	glfwGetWindowSize(m_Window, &m_Width, &m_Height);
}

void Engine::Window::UpdateMouseLocation() {
	glfwGetCursorPos(m_Window, &m_MouseX, &m_MouseY);
}

void Engine::Window::Update() {
	SwapBuffers();
	PollEvents();
	UpdateSize();
}

void Engine::Window::CaptureMouse() {
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Engine::Window::UncaptureMouse() {
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}