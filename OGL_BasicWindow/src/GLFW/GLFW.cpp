#include "GLFW.h"
#include <stdexcept>
GLFW::GLFW() {
	if (!glfwInit()) {
		throw std::runtime_error("Could not initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFW::~GLFW() {
	glfwTerminate();
}