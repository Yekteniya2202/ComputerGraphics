#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloatVec(const std::string& name, glm::vec2 vec);
		void setFloatVec(const std::string& name, glm::vec3 vec);
		void setFloatVec(const std::string& name, glm::vec4 vec);
		void setFloatVec(const std::string& name, float* vec, int vec_size) const;
		void setFloatMat4(const std::string& name, glm::mat4& mat) const;
		~Program();
	};
}

