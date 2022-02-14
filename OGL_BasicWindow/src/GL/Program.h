#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <string>
namespace GL {
	class Program
	{
	private:
		GLuint mProgram;
		GLuint mVertexShader, mFragmentShader;

		GLuint loadShader(const std::string& path, GLenum shaderType);
		GLint getLocation(const std::string& name) const;
	public:
		Program(const std::string& name);
		void link();
		void use();
		void bindAttribute(GLuint index, const std::string& name);
		void setFloat(const std::string& name, float value);
		void setFloatVec(const std::string& name, glm::vec2 vec);
		void setFloatVec(const std::string& name, glm::vec3 vec);
		void setFloatVec(const std::string& name, glm::vec4 vec);
		void setFloatVec(const std::string& name, float* vec, int vec_size) const;
		~Program();
	};
}

