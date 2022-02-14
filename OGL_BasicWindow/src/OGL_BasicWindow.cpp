#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include "GLFW/GLFW.h"
#include "GLFW/Window.h"
struct Color {
	float r, g, b, a;
};


Color background = { 0.f, 0.f, 0.f, 1.f };



int main()
{
	try {
		GLFW glfw;
		Window window("qwerty", 900, 900);
		window.loop();
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}