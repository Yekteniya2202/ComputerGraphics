#include "Window.h"
#include <stdexcept>
#include "../GL/VAO.h"

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

	const char* vertexShaderText = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 inColor;\n"
		"out vec3 fragColor;"
		"void main()\n"
		"{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f); fragColor = inColor;}";

	/*
	std::ifstream sfile;
	sfile.open("basic.vert");
	sfile.read(shaderText, 1000);
	sfile.close();
	*/

	//создаём шейдер
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//прикрепляем код
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	//компилирует шейдер
	glCompileShader(vertexShader);

	//получилось ли скомпилировать шейдер
	char resultInfo[1000];
	int res;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &res);
	if (res == 0) {
		glGetShaderInfoLog(vertexShader, 1000, nullptr, resultInfo);
		throw std::runtime_error("Could not create window");
	}


	const char* fragmeneShaderText = "#version 330 core\n"
		"in vec3 fragColor;\n"
		"out vec4 outColor;\n"
		"void main()\n"
		"{ outColor = vec4(fragColor, 1.0f); }";

	/*
	sfile.open("basic.frag");
	sfile.read(shaderText, 1000);
	sfile.close();
	*/
	//создаём шейдер
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//прикрепляем код
	glShaderSource(fragmentShader, 1, &fragmeneShaderText, nullptr);
	//компилирует шейдер
	glCompileShader(fragmentShader);

	//получилось ли скомпилировать шейдер
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &res);
	if (res == 0) {
		glGetShaderInfoLog(fragmentShader, 1000, nullptr, resultInfo);
		throw std::runtime_error("Could not create window");
	}

	//программа шейдеров
	shaderProg = glCreateProgram();
	//линкуем
	//присоединяем шейдеры
	glAttachShader(shaderProg, vertexShader);
	glAttachShader(shaderProg, fragmentShader);
	//линкуем
	glLinkProgram(shaderProg);
	//получилось ли слинковать шейдер
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &res);
	if (res == 0) {
		glGetProgramInfoLog(shaderProg, 1000, nullptr, resultInfo);
		throw std::runtime_error("Could not create window");
	}

	//удаляем шейдеры 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Window::setContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

void Window::loop()
{
	GL::VAO vao;
	vao.addVertexBufferObject({
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	});
	while (!glfwWindowShouldClose(mWindow)) {
		glUseProgram(shaderProg);
		vao.draw(3);
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}


Window::~Window() {
	glfwDestroyWindow(mWindow);
}