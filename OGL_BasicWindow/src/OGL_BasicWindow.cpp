#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
struct Color {
	float r, g, b, a;
};


Color background = { 0.f, 0.f, 0.f, 1.f };



void OnResize(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
	//std::cout << "Resized to " << width << "x" << height << std::endl;
}

void processInput(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
	if (glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS )
		background.r += background.r <= 1 ? 0.01f : 0;
	if (glfwGetKey(win, GLFW_KEY_2) == GLFW_PRESS)
		background.g += background.g <= 1 ? 0.01f : 0;
	if (glfwGetKey(win, GLFW_KEY_3) == GLFW_PRESS)
		background.b += background.b <= 1 ? 0.01f : 0;
	if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
		background.r -= background.r >= -1 ? 0.01f : 0;
	if (glfwGetKey(win, GLFW_KEY_W)== GLFW_PRESS)
		background.g -= background.g >= -1 ? 0.01f : 0;
	if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
		background.b -= background.b >= -1 ? 0.01f : 0;
	/*
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[2 * 3 + 4] += 0.01f;
	}
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[2 * 3 + 4] -= 0.01f;
	}
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[2 * 3 + 3] += 0.01f;
	}
	if (glfwGetKey(win, GLFW_KEY_F) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[2 * 3 + 3] -= 0.01f;
	}
	if (glfwGetKey(win, GLFW_KEY_G) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[2 * 3 + 5] += 0.01f;
	}
	if (glfwGetKey(win, GLFW_KEY_H) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[2 * 3 + 5] -= 0.01f;
	}

	if (glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[0] += 0.01f;
	}
	if (glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_DYNAMIC_DRAW);
		polygon[0] -= 0.01f;
	}
	*/
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(500, 500, "OpenGL Window", nullptr, nullptr);
	if (win == nullptr)
	{
		std::cout << "Error. Couldn't create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error. Couldn't load GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(win, OnResize);

	glViewport(0, 0, 500, 500);

	

	
	//задаём цель буфера для VBO
	
	//GL_STATIC_DRAW - потому что загружаем полигон один раз и часто отрисовываем

	/*
	GL_STRAEM_DRAW  - записываются один раз и редко будут читаться GPU
	GL_STATIC_DRAW  - записываются один раз и часто будут читаться GPU 
	GL_DYNAMIC_DRAW - записываются много раз и часто будут читаться GPU
	все - под разные типы видеопамяти
	*/

	const int verts = 4;
	float polygon[verts * (3 + 3)] = {
		//			  x     y     z          r     g     b     a

		/*1*/			0.0f,	0.75f,	0.0f,	0.0f, 1.0f, 0.0f,
		/*2*/			0.5f,	0.0f,	0.0f,	0.0f, 0.0f, 1.0f,
		/*3*/			-0.5f,	0.0f,	0.0f,	1.0f, 1.0f, 1.0f,
		/*4*/			0.0f,	-0.75f,	0.0f,	1.0f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	//VAO описывает контекст отрисовки
	unsigned int VAO_Polygon;
	unsigned int EBO_polygon;
	//айди вертексного буфера в видеопамяти с вершинами
	unsigned int VBO_polygon;
	//генерация буфера
	glGenBuffers(1, &VBO_polygon);
	glGenBuffers(1, &EBO_polygon);
	glGenVertexArrays(1, &VAO_Polygon);
	glBindVertexArray(VAO_Polygon);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon);
	//загрузка в видеопамять данных из оперативной памяти
	//                 цель             объем данных      что загружаем   тип
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * (3 + 3), polygon, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_polygon);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (3 + 3), indices, GL_STATIC_DRAW);
	//как данные читать
		//1 - location
		//2 - сколько флоатов на вершину
		//3 - тип данных
		//4 - нормализовано?
		//5 - через сколько байт новая вершина
		//6 - насколько данные смещены относительно нулевого полигона

	//для координат
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 3), (void*)0);
	glEnableVertexAttribArray(0);

	//для цветов
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 3), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
#pragma region Shaders
	//Шейдеры
	//GLSL - OpenGL Shading Language
	//Шейдер - программа, выполняемая на видеокарте. Шейдеры динамически компилируются

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
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
		std::cout << "Shader compilation error: " << resultInfo << std::endl;
		glfwTerminate();
		return -1;
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
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//прикрепляем код
	glShaderSource(fragmentShader, 1, &fragmeneShaderText, nullptr);
	//компилирует шейдер
	glCompileShader(fragmentShader);

	//получилось ли скомпилировать шейдер
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &res);
	if (res == 0) {
		glGetShaderInfoLog(fragmentShader, 1000, nullptr, resultInfo);
		std::cout << "Shader compilation error: " << resultInfo << std::endl;
		glfwTerminate();
		return -1;
	}

	//программа шейдеров
	unsigned int shaderProg;
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
		std::cout << "Shader linking error: " << resultInfo << std::endl;
		glfwTerminate();
		return -1;
	}

	//удаляем шейдеры 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
#pragma endregion
	
	while (!glfwWindowShouldClose(win))
	{
		processInput(win);

		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon);
		

		glUseProgram(shaderProg);
		glBindVertexArray(VAO_Polygon);

		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}