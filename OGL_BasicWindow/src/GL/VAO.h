#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>
namespace GL {
	class VAO
	{
	private:
		GLuint mVao;
		std::vector<GLuint> mBuffers;
		unsigned mIndicesBuffer;
		size_t mIndicesCount = 0;
	public:
		VAO();
		VAO(const VAO&) = delete;
		void bind();
		void setIndicesCount(unsigned count);
		void addVertexBufferObject(const std::vector<float>& data);
		void addVertexBufferObject(const std::vector<glm::vec2>& data);
		void addVertexBufferObject(const std::vector<glm::vec3>& data);
		void addVertexBufferObject(const std::vector<glm::vec4>& data);
		void draw(unsigned type);
		void addIndices(const std::vector<unsigned>& data);
		void addIndices(const std::vector<glm::vec3>& data);
		~VAO();
	};
}

