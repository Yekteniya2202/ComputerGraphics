#pragma once
#include "VAO.h"
#include <vector>

struct ModelTransform {

	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 scale;

	void setScale(float s) {
		scale.x = s;
		scale.y = s;
		scale.z = s;
	}
};

typedef unsigned char byte;
class Model
{
private:
	GL::VAO vao;
	std::vector<glm::vec3> points;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texture;
	std::vector<unsigned> indices;
	byte* data;
	int box_width, box_height, channels;
	unsigned int box_texture;
	ModelTransform polygonTrans = { glm::vec3(0.0f, 0.0f, 0.0f), //pos
									glm::vec3(0.f, 0.f, 0.f), //rotation
									glm::vec3(1.f, 1.f, 1.f) }; //scale 
	glm::mat4 model = glm::mat4(1.0f);

	void Update();
public:
	Model() = delete;
	//Model(std::vector<glm::vec3> points, std::vector<glm::vec3> colors, std::vector<glm::vec2> texture, std::vector<unsigned> indices);
	Model(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec2> texture, std::vector<glm::vec3> colors);
	Model(const Model& other);
	void SetPolygonTrans(ModelTransform pt);
	void GenTexture();
	void Draw(GLenum type);
	void SetRotationX(float degree);
	void SetRotationY(float degree);
	void SetRotationZ(float degree);
	void SetPosX(float pos);
	void SetPosY(float pos);
	void SetPosZ(float pos);
	void SetScale(float k);
	
	glm::mat4 GetModel() const;
	~Model();
};

