#include "Model.h"
#include <glm/ext/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

void Model::Update()
{
	model = glm::mat4(1.0f);
	this->model = glm::translate(model, polygonTrans.pos);
	this->model = glm::rotate(model, glm::radians(polygonTrans.rotation.x), glm::vec3(1.f, 0.f, 0.f)); // вокруг x
	this->model = glm::rotate(model, glm::radians(polygonTrans.rotation.y), glm::vec3(0.f, 1.f, 0.f)); // вокруг y
	this->model = glm::rotate(model, glm::radians(polygonTrans.rotation.z), glm::vec3(0.f, 0.f, 1.f)); // вокруг z
	this->model = glm::scale(model, polygonTrans.scale);
}

Model::Model(std::vector<glm::vec3> points, std::vector<glm::vec3> colors, std::vector<glm::vec2> texture, std::vector<unsigned> indices)
{
	this->points = points;
	this->colors = colors;
	this->indices = indices;
	vao.addVertexBufferObject(points);
	vao.addVertexBufferObject(colors);
	vao.addVertexBufferObject(texture);
	vao.addIndices(indices);
	Update();
}

void Model::GenTexture()
{
	glGenTextures(1, &box_texture);
	data = stbi_load("images/roflan.jpg", &box_width, &box_height, &channels, 0);

	glBindTexture(GL_TEXTURE_2D, box_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (channels == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, box_width, box_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, box_width, box_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
}

void Model::Draw(GLenum type)
{

	Update();
	vao.draw(type);
}

void Model::SetRotationX(float degree)
{
	polygonTrans.rotation.x = degree;
}

void Model::SetRotationY(float degree)
{
	polygonTrans.rotation.y = degree;
}

void Model::SetRotationZ(float degree)
{
	polygonTrans.rotation.z = degree;
}

void Model::SetPosX(float pos)
{
	polygonTrans.pos.x = pos;
}

void Model::SetPosY(float pos)
{
	polygonTrans.pos.y = pos;
}

void Model::SetPosZ(float pos)
{
	polygonTrans.pos.z = pos;
}

void Model::SetScale(float k)
{
	polygonTrans.setScale(k);
}


glm::mat4 Model::GetModel() const
{
	return model;
}

Model::~Model()
{
}
