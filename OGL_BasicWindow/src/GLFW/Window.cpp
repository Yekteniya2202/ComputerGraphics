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
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
}

void Window::setContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

void Window::loop()
{
	GL::VAO vao;
	vao.addVertexBufferObject({
		{-1.0f,	1.0f,	-1.0f},
		{1.0f,	1.0f,	-1.0f},		
		{1.0f,	1.0f,	1.0f},		
		{-1.0f,	1.0f,	1.0f},		
		{-1.0f,	-1.0f,	-1.0f},		
		{1.0f,	-1.0f,	-1.0f},		
		{1.0f,	-1.0f,	1.0f},		
		{-1.0f,	-1.0f,	1.0f}
	});
	vao.addVertexBufferObject({
		{1.0f, 0.0f, 0.0f},
		{0.5f, 0.5f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.5f, 0.5f},
		{0.0f, 0.0f, 1.0f},
		{0.5f, 0.0f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{1.0f, 1.0f, 1.0f}
	});
	vao.addIndices({
		0,1,3,
		1,2,3,
		0,4,1,
		1,4,5,
		0,3,7,
		0,7,4,
		1,6,2,
		1,5,6,
		2,7,3,
		2,6,7,
		4,7,5,
		5,7,6
	});

	Model myCube({
		{-1.0f,	1.0f,	-1.0f},
		{1.0f,	1.0f,	-1.0f},
		{1.0f,	1.0f,	1.0f},
		{-1.0f,	1.0f,	1.0f},
		{-1.0f,	-1.0f,	-1.0f},
		{1.0f,	-1.0f,	-1.0f},
		{1.0f,	-1.0f,	1.0f},
		{-1.0f,	-1.0f,	1.0f}
		},{
		{1.0f, 0.0f, 0.0f},
		{0.5f, 0.5f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.5f, 0.5f},
		{0.0f, 0.0f, 1.0f},
		{0.5f, 0.0f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{1.0f, 1.0f, 1.0f}
		},{
		0,1,3,
		1,2,3,
		0,4,1,
		1,4,5,
		0,3,7,
		0,7,4,
		1,6,2,
		1,5,6,
		2,7,3,
		2,6,7,
		4,7,5,
		5,7,6
		});

	
	myCube.SetScale(0.5f);
	GL::Program first("first");
	first.bindAttribute(0, "position");
	first.link();
	first.use();
	float anim = 0.f;

	
	while (!glfwWindowShouldClose(mWindow)) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		myCube.SetRotationX(glfwGetTime() * 45.0);
		myCube.SetRotationZ(glfwGetTime() * 60.0);
		myCube.SetPosX(0.8f * cos(glfwGetTime()));
		myCube.SetPosY(0.8f * sin(glfwGetTime()));
		myCube.SetScale(0.2f);
		glm::mat4 model = myCube.GetModel();
		first.setFloatMat4("model", model);
		myCube.Draw(GL_TRIANGLES);

		myCube.SetRotationY(glfwGetTime() * 45.0);
		myCube.SetRotationZ(glfwGetTime() * 30.0);
		myCube.SetPosX(0.8f * cos(glfwGetTime() + 3.14158f));
		myCube.SetPosY(0.8f * sin(glfwGetTime() + 3.14158f));
		model = myCube.GetModel();
		first.setFloatMat4("model", model);
		myCube.Draw(GL_TRIANGLES);

		myCube.SetRotationZ(0);
		myCube.SetPosX(0);
		myCube.SetPosY(0);
		myCube.SetRotationY(glfwGetTime() * 90.0);
		myCube.SetRotationX(glfwGetTime() * 60.0);
		model = myCube.GetModel();
		first.setFloatMat4("model", model);
		myCube.Draw(GL_TRIANGLES);

		/*
		polygonTrans.rotation.z = glfwGetTime() * 60.0;
		polygonTrans.rotation.x = glfwGetTime() * 45.0;
		polygonTrans.pos.x = 0.8f * cos(glfwGetTime());
		polygonTrans.pos.y = 0.8f * sin(glfwGetTime());
		polygonTrans.setScale(0.2f);
		
		polygonTrans2.rotation.z = glfwGetTime() * 30.0;
		polygonTrans2.rotation.y = glfwGetTime() * 45.0;
		polygonTrans2.pos.x = 0.8f * cos(glfwGetTime() + 3.14158f);
		polygonTrans2.pos.y = 0.8f * sin(glfwGetTime() + 3.14158f);


		polygonTrans2.setScale(0.2f);
		polygonTrans3.setScale(0.2f);
		polygonTrans3.rotation.x = glfwGetTime() * 90.0;
		polygonTrans3.rotation.y = glfwGetTime() * 60.0;
		
		*/

		
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}


Window::~Window() {
	glfwDestroyWindow(mWindow);
}