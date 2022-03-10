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

	Model lightCube(myCube);
	lightCube.GenTexture();

	GL::Program light("light");
	light.bindAttribute(1, "position");
	light.link();
	light.use();
	float anim = 0.f;
	
	double oldTime = glfwGetTime(), newTime, deltaTime;

	glm::vec3 lightPos = glm::vec3(5.0f, 0.f, 0.f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(mWindow)) {
		newTime = glfwGetTime();
		deltaTime = newTime - oldTime;
		oldTime = newTime;
		processInput(deltaTime);

		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 pv = camera.GetProjectionMatrix() * camera.GetViewMatrix();

		myCube.SetPolygonTrans({ glm::vec3(0.0f, 0.0f, 0.0f), //pos
									glm::vec3(0.f, 0.f, 0.f), //rotation
									glm::vec3(1.f, 1.f, 1.f) }); //scale )

		//myCube.SetRotationX(glfwGetTime() * 45.0);
		myCube.SetRotationZ(glfwGetTime() * 60.0);
		myCube.SetPosX(0.6f * cos(glfwGetTime()));
		myCube.SetPosY(0.6f * sin(glfwGetTime()));
		myCube.SetScale(0.2f);
		glm::mat4 model = myCube.GetModel();

		first.use();
		first.setFloatMat4("pv", pv);
		first.setFloatMat4("model", model);
		first.setFloatVec("viewPos", camera.Position);
		first.setFloatVec("lightPos", lightPos);
		first.setFloatVec("lightColor", lightColor);
		first.setFloatVec("ambientColor", ambientColor);
		first.setBool("wireFrameMode", wireframeMode);
		
		myCube.Draw(GL_TRIANGLES);

		//myCube.SetRotationY(glfwGetTime() * 45.0);
		myCube.SetRotationZ(glfwGetTime() * 30.0);
		myCube.SetPosX(0.6f * cos(glfwGetTime() + 3.14158f));
		myCube.SetPosY(0.6f * sin(glfwGetTime() + 3.14158f));
		model = myCube.GetModel();

		first.use();
		first.setFloatMat4("pv", pv);
		first.setFloatMat4("model", model);
		first.setFloatVec("viewPos", camera.Position);
		first.setFloatVec("lightPos", lightPos);
		first.setFloatVec("lightColor", lightColor);
		first.setFloatVec("ambientColor", ambientColor);
		first.setBool("wireFrameMode", wireframeMode);

		myCube.Draw(GL_TRIANGLES);

		//статический кубик
		myCube.SetRotationZ(0);
		myCube.SetPosX(0);
		myCube.SetPosY(0);
		//myCube.SetRotationY(glfwGetTime() * 90.0);
		//myCube.SetRotationX(glfwGetTime() * 60.0);
		model = myCube.GetModel();

		first.use();
		first.setFloatMat4("pv", pv);
		first.setFloatMat4("model", model);
		first.setFloatVec("viewPos", camera.Position);
		first.setFloatVec("lightPos", lightPos);
		first.setFloatVec("lightColor", lightColor);
		first.setFloatVec("ambientColor", ambientColor);
		first.setBool("wireFrameMode", wireframeMode);

		myCube.Draw(GL_TRIANGLES);


		
		//LIGHT
		lightCube.SetPolygonTrans({ glm::vec3(0.0f, 0.0f, 0.0f), //pos
									glm::vec3(0.f, 0.f, 0.f), //rotation
									glm::vec3(0.2f, 0.2f, 0.2f) }); //scale )

		lightCube.SetPosX(5.0f * cos(glfwGetTime() * 1.2f));
		lightCube.SetPosZ(5.0f * sin(glfwGetTime() * 1.2f));
		lightPos.x = 5.0f * cos(glfwGetTime() * 1.2f);
		lightPos.z = 5.0f * sin(glfwGetTime() * 1.2f);
		model = lightCube.GetModel();
		light.use();
		light.setFloatMat4("pv", pv);
		light.setFloatMat4("model", model);
		light.setFloatVec("lightColor", lightColor);

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