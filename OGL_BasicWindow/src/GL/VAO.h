#pragma once
#include	<glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
namespace GL {
	class VAO
	{
	private:
		GLuint mVao;
		std::vector<GLuint> mBuffers;
	public:
		VAO();
		VAO(const VAO&) = delete;
		void bind();
		void addVertexBufferObject(const std::vector<float>& data);
		void draw(GLsizei count);
		~VAO();
	};
}

