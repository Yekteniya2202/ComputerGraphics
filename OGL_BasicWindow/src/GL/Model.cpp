#include "Model.h"
#include <glm/ext/matrix_transform.hpp>

void Model::Update()
{
	model = glm::mat4(1.0f);
	this->model = glm::translate(model, polygonTrans.pos);
	this->model = glm::rotate(model, glm::radians(polygonTrans.rotation.x), glm::vec3(1.f, 0.f, 0.f)); // вокруг x
	this->model = glm::rotate(model, glm::radians(polygonTrans.rotation.y), glm::vec3(0.f, 1.f, 0.f)); // вокруг y
	this->model = glm::rotate(model, glm::radians(polygonTrans.rotation.z), glm::vec3(0.f, 0.f, 1.f)); // вокруг z
	this->model = glm::scale(model, polygonTrans.scale);
}

Model::Model(std::vector<glm::vec3> points, std::vector<glm::vec3> colors, std::vector<unsigned> indices)
{
	this->points = points;
	this->colors = colors;
	this->indices = indices;
	vao.addVertexBufferObject(points);
	vao.addVertexBufferObject(colors);
	vao.addIndices(indices);
	Update();
}

void Model::Draw(GLenum type)
{
	Update();
	vao.draw(GL_TRIANGLES);
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
