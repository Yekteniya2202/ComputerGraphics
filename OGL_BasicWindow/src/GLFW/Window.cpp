#include "Window.h"
#include <stdexcept>
#include "../GL/Camera.h"
#include <iostream>
float cam_dist = 5.0f;
bool wireframeMode = false;
Camera camera(glm::vec3(0.f, 0.f, -5.f));

struct Color2 {
	float r, g, b, a;
};

Color2 background = { 0.f, 0.f, 0.f, 1.f };
void OnResize2(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}

void UpdatePolygoneMode()
{
	if (wireframeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OnKeyAction(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_SPACE:
			wireframeMode = !wireframeMode;
			UpdatePolygoneMode();
			break;
		}
	}
}

void OnScroll(GLFWwindow* win, double x, double y)
{
	camera.ChangeFOV(y);
	std::cout << "Scrolled x: " << x << ", y: " << y << ". FOV = " << camera.Fov << std::endl;
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
	glfwSetScrollCallback(mWindow, OnScroll);
	glfwSetKeyCallback(mWindow, OnKeyAction);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	UpdatePolygoneMode();

}

void Window::setContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

void Window::loop()
{

	Model myCube({
		//вершины
	{-1.0f,	-1.0f,	-1.0f},
	{-1.0f,	-1.0f,	1.0f},
	{-1.0f, 1.0f,	1.0f},
	{-1.0f,	-1.0f,	-1.0f},
	{-1.0f, 1.0f,	1.0f},
	{-1.0f, 1.0f,	-1.0f},

	{1.0f,	1.0f,	-1.0f },
	{-1.0f,	-1.0f,	-1.0f},
	{-1.0f, 1.0f,	-1.0f},
	{1.0f,	1.0f,	-1.0f },
	{1.0f,	-1.0f,	-1.0f },
	{-1.0f,	-1.0f,	-1.0f},

	{1.0f,	-1.0f,	1.0f },
	{-1.0f,	-1.0f,	-1.0f},
	{1.0f,	-1.0f,	-1.0f },
	{1.0f,	-1.0f,	1.0f },
	{-1.0f,	-1.0f,	1.0f},
	{-1.0f,	-1.0f,	-1.0f},

	{-1.0f, 1.0f,	1.0f},
	{-1.0f,	-1.0f,	1.0f},
	{1.0f,	-1.0f,	1.0f },
	{1.0f,	1.0f,	1.0f },
	{-1.0f, 1.0f,	1.0f},
	{1.0f,	-1.0f,	1.0f },

	{1.0f,	 1.0f,	1.0f },
	{1.0f,	-1.0f,	-1.0f },
	{1.0f,	 1.0f,	-1.0f },
	{1.0f,	-1.0f,	-1.0f },
	{1.0f,	1.0f,	1.0f },
	{1.0f,	-1.0f,	1.0f },

	{1.0f,	1.0f,	1.0f },
	{1.0f,	1.0f,	-1.0f },
	{-1.0f, 1.0f,	-1.0f},
	{1.0f,	1.0f,	1.0f },
	{-1.0f, 1.0f,	-1.0f},
	{-1.0f, 1.0f,	1.0f}
	//нормали
		}, {
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},
	{-1.0f,  0.0f,  0.0f},

	{0.0f,  0.0f, -1.0f },
	{0.0f,  0.0f, -1.0f },
	{0.0f,  0.0f, -1.0f },
	{0.0f,  0.0f, -1.0f },
	{0.0f,  0.0f, -1.0f },
	{0.0f,  0.0f, -1.0f },

	{0.0f, -1.0f,  0.0f },
	{0.0f, -1.0f,  0.0f },
	{0.0f, -1.0f,  0.0f },
	{0.0f, -1.0f,  0.0f },
	{0.0f, -1.0f,  0.0f },
	{0.0f, -1.0f,  0.0f },

	{0.0f,  0.0f, 1.0f  },
	{0.0f,  0.0f, 1.0f  },
	{0.0f,  0.0f, 1.0f  },
	{0.0f,  0.0f, 1.0f  },
	{0.0f,  0.0f, 1.0f  },
	{0.0f,  0.0f, 1.0f  },

	{1.0f,  0.0f,  0.0f },
	{1.0f,  0.0f,  0.0f },
	{1.0f,  0.0f,  0.0f },
	{1.0f,  0.0f,  0.0f },
	{1.0f,  0.0f,  0.0f },
	{1.0f,  0.0f,  0.0f },

	{0.0f,  1.0f,  0.0f },
	{0.0f,  1.0f,  0.0f },
	{0.0f,  1.0f,  0.0f },
	{0.0f,  1.0f,  0.0f },
	{0.0f,  1.0f,  0.0f },
	{0.0f,  1.0f,  0.0f }
	//текстуры
		}, {
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},

	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},

	{0.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},

	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f, 0.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f}
	//цвета
		}, {
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},

	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},

	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},

	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},

	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f}
		}
		);

	myCube.GenTexture();
	myCube.SetScale(0.5f);
	GL::Program first("first");
	first.bindAttribute(0, "position");
	first.link();

	Material cubeMaterials[3] =
	{
		{	glm::vec3(0.25, 0.20725, 0.20725),
			glm::vec3(1, 0.829, 0.829),
			glm::vec3(0.296648, 0.296648, 0.296648),
			12.f
		},

		{	glm::vec3(0.25, 0.25, 0.25),
			glm::vec3(0.4, 0.4, 0.4),
			glm::vec3(0.774597, 0.774597, 0.774597),
			77.f
		},

		{	glm::vec3(0.1742, 0.01175, 0.01175),
			glm::vec3(0.61424, 0.014136, 0.014136),
			glm::vec3(0.727811, 0.626959, 0.626959),
			77.f
		}
	};

	Model lightCube(myCube);
	lightCube.GenTexture();

	GL::Program light("light");
	light.bindAttribute(1, "position");
	light.link();
	light.use();
	float anim = 0.f;

	
	double oldTime = glfwGetTime(), newTime, deltaTime;

	PointLight light1 = {
		glm::vec3(5.0f, 0.f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(3.0f, 3.0f, 3.0f),
		0.9f, 0.1f, 0.09f
	};

	const int cube_count = 100;
	ModelTransform cubeTrans[cube_count];
	int cubeMat[cube_count];
	for (int i = 0; i < cube_count; i++) {
		float scale = (rand() % 6 + 1) / 20.0f;
		cubeTrans[i] = {
			glm::vec3((rand() % 101 - 50) / 10.0f, (rand() % 101 - 50) / 10.0f, (rand() % 101 - 50) / 10.0f),
			glm::vec3(rand() / 100.0f, rand() / 100.0f, rand() / 100.0f),
			glm::vec3(scale, scale, scale)
		};
		cubeMat[i] = rand() % 3;
	}
	while (!glfwWindowShouldClose(mWindow)) {
		newTime = glfwGetTime();
		deltaTime = newTime - oldTime;
		oldTime = newTime;
		processInput(deltaTime);

		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 pv = camera.GetProjectionMatrix() * camera.GetViewMatrix();

		glm::mat4 model;
		for (int i = 0; i < cube_count; i++) {
			myCube.SetPolygonTrans(cubeTrans[i]);
			model = myCube.GetModel();


			first.use();
			first.setFloatMat4("pv", pv);
			first.setFloatMat4("model", model);
			first.setFloatVec("viewPos", camera.Position);
			first.setFloatVec("light.position", light1.position);
			first.setFloatVec("light.ambient", light1.ambient);
			first.setFloatVec("light.diffuse", light1.diffuse);
			first.setFloatVec("light.specular", light1.specular);
			first.setFloat("light.constant", light1.constant);
			first.setFloat("light.linear", light1.linear);
			first.setFloat("light.quadratic", light1.quadratic);
			first.setBool("wireFrameMode", wireframeMode);
			first.setFloatVec("material.ambient", cubeMaterials[cubeMat[i]].ambient);
			first.setFloatVec("material.diffuse", cubeMaterials[cubeMat[i]].diffuse);
			first.setFloatVec("material.specular", cubeMaterials[cubeMat[i]].specular);
			first.setFloat("material.shininess", cubeMaterials[cubeMat[i]].shininess);

			myCube.Draw(GL_TRIANGLES);
		}
		
		//LIGHT

		light1.position.x = 0.0f; // *cos(glfwGetTime() * 1.2f);
		light1.position.z = 0.0f; // *sin(glfwGetTime() * 1.2f);
		lightCube.SetPolygonTrans({ light1.position, //pos
									glm::vec3(0.f, 0.f, 0.f), //rotation
									glm::vec3(0.2f, 0.2f, 0.2f) }); //scale )
		model = lightCube.GetModel();
		light.use();
		light.setFloatMat4("pv", pv);
		light.setFloatMat4("model", model);
		light.setFloatVec("lightColor", light1.specular);

		lightCube.Draw(GL_TRIANGLES);

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Window::processInput(float dt)
{
	uint32_t dir = 0;
	if (glfwGetKey(mWindow, GLFW_KEY_1) == GLFW_PRESS)
		background = { 1.0f, 0.0f, 0.0f, 1.0f };
	if (glfwGetKey(mWindow, GLFW_KEY_2) == GLFW_PRESS)
		background = { 0.0f, 1.0f, 0.0f, 1.0f };
	if (glfwGetKey(mWindow, GLFW_KEY_3) == GLFW_PRESS)
		background = { 0.0f, 0.0f, 1.0f, 1.0f };
	if (glfwGetKey(mWindow, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		dir |= CAM_UP;
	if (glfwGetKey(mWindow, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		dir |= CAM_DOWN;
	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
		dir |= CAM_FORWARD;
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
		dir |= CAM_BACKWARD;
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
		dir |= CAM_LEFT;
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
		dir |= CAM_RIGHT;
	
	
	static double newx = 0.f, newy = 0.f;
	glfwGetCursorPos(mWindow, &newx, &newy);

	static double x = newx, y = newy;
	double xoffset = newx - x;
	double yoffset = newy - y;
	x = newx;
	y = newy;

	camera.Move(dir, dt);
	camera.Rotate(xoffset, -yoffset);

}


Window::~Window() {
	glfwDestroyWindow(mWindow);
}