#pragma once
#include <glad\glad.h>
#include <string>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "../GL/VAO.h"
#include "../GL/Program.h"

class Window {
private:
	GLFWwindow* mWindow;
	unsigned int vertexShader, fragmentShader, shaderProg;
public:
	Window(const std::string& title, int width, int height);
	void setContextCurrent();
	void loop();
	~Window();
};