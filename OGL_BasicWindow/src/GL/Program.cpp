#include "Program.h"
#include <fstream>
#include <iterator>
#include <iostream>
GLuint GL::Program::loadShader(const std::string& path, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	std::ifstream fis(path);
	std::string shaderCode = { std::istreambuf_iterator<char>(fis), std::istreambuf_iterator<char>() };

	const char* c = shaderCode.c_str();
	glShaderSource(shader, 1, &c, nullptr);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	char buf[0x1000];
	GLsizei len;
	glGetShaderInfoLog(shader, sizeof(buf), &len, buf);
	if (len > 0) {
		throw std::runtime_error(buf);
	}

	return shader;
}

GLint GL::Program::getLocation(const std::string& name) const
{
	return glGetUniformLocation(mProgram, name.c_str());
}

void GL::Program::setFloat(const std::string& name, float value)
{
	glUniform1f(getLocation(name), value);
}

void GL::Program::setBool(const std::string& name, bool value)
{
	glUniform1i(getLocation(name), value);
}

void GL::Program::setInt(const std::string& name, int value)
{
	glUniform1i(getLocation(name), value);
}

void GL::Program::setFloatVec(const std::string& name, glm::vec2 vec)
{
	glUniform2f(getLocation(name), vec[0], vec[1]);
}

void GL::Program::setFloatVec(const std::string& name, glm::vec3 vec)
{
	glUniform3f(getLocation(name), vec[0], vec[1], vec[2]);
}

void GL::Program::setFloatVec(const std::string& name, glm::vec4 vec)
{
	glUniform4f(getLocation(name), vec[0], vec[1], vec[2], vec[3]);
}

void GL::Program::setFloatVec(const std::string& name, float* vec, int vec_size) const
{
	switch (vec_size)
	{
	case 1: glUniform1f(getLocation(name), vec[0]); break;
	case 2: glUniform2f(getLocation(name), vec[0], vec[1]); break;
	case 3: glUniform3f(getLocation(name), vec[0], vec[1], vec[2]); break;
	case 4: glUniform4f(getLocation(name), vec[0], vec[1], vec[2], vec[3]); break;
	default: std::cout << "SHADER FAILURE! NO SUCH UNIFORM VECTOR SIZE!" << std::endl;
	}
}

void GL::Program::setFloatMat4(const std::string& name, glm::mat4& mat) const
{
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}


void GL::Program::link()
{
	glAttachShader(mProgram, mVertexShader);
	glAttachShader(mProgram, mFragmentShader);
	glLinkProgram(mProgram);
}

void GL::Program::use()
{
	glUseProgram(mProgram);
}

void GL::Program::bindAttribute(GLuint index, const std::string& name)
{
	glBindAttribLocation(mProgram, index, name.c_str());
}


GL::Program::Program(const std::string& name)
{
	mProgram = glCreateProgram();
	mVertexShader = loadShader("res/glsl/" + name + ".vert", GL_VERTEX_SHADER);
	mFragmentShader = loadShader("res/glsl/" + name + ".frag", GL_FRAGMENT_SHADER);
}

GL::Program::~Program()
{
	glDetachShader(mProgram, mVertexShader);
	glDetachShader(mProgram, mFragmentShader);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	glDeleteProgram(mProgram);
}
