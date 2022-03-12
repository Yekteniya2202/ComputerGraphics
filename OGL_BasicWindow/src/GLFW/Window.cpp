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

	Light lights[10];
	int lights_count = 3;

	lights[0].type = LightType::Point;
	lights[0].position = glm::vec3(0.0f, 0.f, 0.f);
	lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights[0].diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	lights[0].specular = glm::vec3(3.0f, 3.0f, 3.0f);
	lights[0].constant = 1.0f;
	lights[0].linear = 0.1f;
	lights[0].quadratic = 0.09f;
	

	lights[1].type = LightType::Directional;
	lights[1].direction = glm::vec3(-1.0f, -1.0f, -1.0f);
	lights[1].ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	lights[1].diffuse = glm::vec3(0.6f, 0.85f, 1.0f);
	lights[1].specular = glm::vec3(0.0f, 0.0f, 0.0f);
		 
	lights[2].type = LightType::Spot;
	lights[2].position = glm::vec3(0.0f, 0.0f, 0.0f);
	lights[2].direction = glm::vec3(0.0f, 0.0f, 0.0f);
	lights[2].cutOff = glm::radians(10.0f);
	lights[2].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights[2].diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	lights[2].specular = glm::vec3(3.0f, 3.0f, 3.0f);
	lights[2].constant = 1.0f;
	lights[2].linear = 0.1f;
	lights[2].quadratic = 0.09f;

	const int cube_count = 200;
	ModelTransform cubeTrans[cube_count];
	int cubeMat[cube_count];
	for (int i = 0; i < cube_count; i++) {
		float scale = (rand() % 6 + 1) / 20.0f;
		cubeTrans[i] = {
			glm::vec3((rand() % 61 - 30) / 10.0f, (rand() % 61 - 30) / 10.0f, (rand() % 61 - 30) / 10.0f),
			glm::vec3(rand() / 100.0f, rand() / 100.0f, rand() / 100.0f),
			glm::vec3(scale, scale, scale)
		};
		cubeMat[i] = rand() % 3;

		
		if ((glm::vec3(0, 0, 0) - cubeTrans[i].pos).length() < 0.7)
			i--;
	}
	while (!glfwWindowShouldClose(mWindow)) {
		newTime = glfwGetTime();
		deltaTime = newTime - oldTime;
		oldTime = newTime;
		processInput(deltaTime);

		lights[2].position = camera.Position - camera.Up * 0.3f;
		lights[2].direction = camera.Front;
		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 pv = camera.GetProjectionMatrix() * camera.GetViewMatrix();
		glm::mat4 model;
		first.use();
		first.setFloatMat4("pv", pv);
		first.setFloatVec("viewPos", camera.Position);
		first.setBool("wireFrameMode", wireframeMode);
		for (int i = 0; i < cube_count; i++) {
			myCube.SetPolygonTrans(cubeTrans[i]);
			model = myCube.GetModel();


			

			first.setFloatMat4("model", model);
			first.setInt("lights_count", lights_count);

			for(int i = 0; i < lights_count; i++)
			{
				
				std::string num = std::to_string(i);
				switch (lights[i].type) {
					case LightType::Directional:
						first.setInt("light["+num+"].type", (int)lights[i].type);
						first.setFloatVec("light["+num+"].direction", lights[i].direction);
						first.setFloatVec("light["+num+"].ambient", lights[i].ambient);
						first.setFloatVec("light["+num+"].diffuse", lights[i].diffuse);
						first.setFloatVec("light["+num+"].specular", lights[i].specular);
					break;

					case LightType::Point:
						first.setInt("light[" + num + "].type", (int)lights[i].type);
						first.setFloatVec("light[" + num + "].position", lights[i].position);
						first.setFloatVec("light[" + num + "].ambient", lights[i].ambient);
						first.setFloatVec("light[" + num + "].diffuse", lights[i].diffuse);
						first.setFloatVec("light[" + num + "].specular", lights[i].specular);
						first.setFloat("light[" + num + "].constant", lights[i].constant);
						first.setFloat("light[" + num + "].linear", lights[i].linear);
						first.setFloat("light[" + num + "].quadratic", lights[i].quadratic);
					break;

					case LightType::Spot:
						first.setInt("light[" + num + "].type", (int)lights[i].type);
						first.setFloatVec("light[" + num + "].position", lights[i].position);
						first.setFloatVec("light[" + num + "].direction", lights[i].direction);
						first.setFloat("light[" + num + "].cutOff", lights[i].cutOff);
						first.setFloatVec("light[" + num + "].ambient", lights[i].ambient);
						first.setFloatVec("light[" + num + "].diffuse", lights[i].diffuse);
						first.setFloatVec("light[" + num + "].specular", lights[i].specular);
						first.setFloat("light[" + num + "].constant", lights[i].constant);
						first.setFloat("light[" + num + "].linear", lights[i].linear);
						first.setFloat("light[" + num + "].quadratic", lights[i].quadratic);
					break;

				}
			}

			first.setFloatVec("material.ambient",	cubeMaterials[cubeMat[i]].ambient);
			first.setFloatVec("material.diffuse",	cubeMaterials[cubeMat[i]].diffuse);
			first.setFloatVec("material.specular",	cubeMaterials[cubeMat[i]].specular);
			first.setFloat("material.shininess",	cubeMaterials[cubeMat[i]].shininess);

			myCube.Draw(GL_TRIANGLES);
		}
		
		//LIGHT
		lightCube.SetPolygonTrans({ glm::vec3(0.f, 0.f, 0.f), //pos
									glm::vec3(0.f, 0.f, 0.f), //rotation
									glm::vec3(0.2f, 0.2f, 0.2f) }); //scale )
		model = lightCube.GetModel();
		light.use();
		light.setFloatMat4("pv", pv);
		light.setFloatMat4("model", model);

		light.setFloatVec("lightColor", glm::vec3(1,1,1));

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
	if (glfwGetKey(mWindow, GLFW_KEY_4) == GLFW_PRESS)
		background = { 0.0f, 0.0f, 0.0f, 1.0f };
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