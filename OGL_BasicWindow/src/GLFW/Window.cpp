#include "Window.h"
#include <stdexcept>


void OnResize2(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const std::string& title, int width, int height) {
	mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (mWindow == nullptr) {
		throw std::runtime_error("Could not create window");
	}
	setContextCurrent();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Could not load Glad");
	}
	glfwSetFramebufferSizeCallback(mWindow, OnResize2);
	glViewport(0, 0, 500, 500);
}

void Window::setContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

void Window::loop()
{
	GL::VAO vao;
	vao.addVertexBufferObject({
		{0.0f, 0.5f, 0.0f},
		{-0.5f, 0.0f, 0.0f},//
		{0.5f, 0.0f, 0.0f},//
		{0.0f, -0.5f, 0.0f},
	});
	vao.addVertexBufferObject({
		{1, 0, 0},
		{0, 0, 1},
		{0, 1, 0},
		{1, 0, 0}
	});
	vao.addIndices({
		0,1,2,
		2,1,3
	});

	float pos[3] = { 1.0f, 0.0f, 1.f };
	GL::Program first("first");
	first.bindAttribute(0, "position");
	first.link();
	first.use();
	float anim = 0.f;
	while (!glfwWindowShouldClose(mWindow)) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		anim += 0.001f;

		pos[0] = sin(anim * 0.5f + 0.5f);
		pos[1] = cos(anim * 0.5f + 0.5f);
		pos[2] = 0;
		first.setFloat("animation", cos(anim * 0.5f + 0.5f));
		first.setFloatVec("uniformPos", pos, 3);
		vao.draw(GL_TRIANGLES);
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}


Window::~Window() {
	glfwDestroyWindow(mWindow);
}