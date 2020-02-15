#include "Box.h"
#include<gtc/matrix_transform.hpp>


Box::Box(std::vector<std::unique_ptr<Mesh>>& cubeType,
	float x, float y, float z) : pos(glm::vec3(x, y, z)), 
	scaleAll(1.f), rotationAxis(glm::vec3(1.f, 0.f,0.f)), rotationDegree(0.f), type(&cubeType)
{
	calculateMatrix();
}

void Box::move(glm::vec3 offset) {
	setPos(getPos() + offset);
}
//For model matrix
void Box::setPos(glm::vec3 Position) {
	pos = Position;
	calculateMatrix();
}

void Box::rotate(glm::vec3 RotateAxis, float RotateDegree) {
	rotationAxis = RotateAxis;
	rotationDegree = RotateDegree;
	calculateMatrix();
}
void Box::scale(float Scale) {
	scaleAll = Scale;
	calculateMatrix();
}

void Box::calculateMatrix() {
	modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleAll));
	modelMatrix = glm::translate(modelMatrix, pos);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDegree), rotationAxis);
}

std::vector<std::unique_ptr<Mesh>> Box::dirtCube;
std::vector<std::unique_ptr<Mesh>> Box::grassCube;

void Box::drawCubeMesh(std::shared_ptr<Shader>& shader) {
	shader->setUniformMatrix4f("model", getModelMatrix());
	for (auto& m : *type)
		m->draw(shader);
}


void Box::init() {
	std::vector<Vertex> backVec{
		// positions          // normals           // texture coords   //x left right, y up bottom, z back front
		{{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f}},//l b b ///BACK FACE
		{{ 0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f,  0.0f}},//r b b
		{{ 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f}},//r u b
		{{ 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f}},//r u b
		{{-0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f,  1.0f}},//l u b
		{{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f}} //l b b
	};
	std::vector<Vertex> frontVec{
		{{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f,  0.0f}},//l b f //FRONT FACE
		{{ 0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f,  0.0f}},//r b f
		{{ 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f,  1.0f}},//r u f
		{{ 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f,  1.0f}},//r u f
		{{-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f,  1.0f}},//l u f
		{{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f,  0.0f}} //l b f
	};
	std::vector<Vertex> leftVec{
		{{-0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  1.0f}},//l u f //LEFT FACE
		{{-0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f}},//l u b
		{{-0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  0.0f}},//l b b
		{{-0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  0.0f}},//l b b
		{{-0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f}},//l b f
		{{-0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  1.0f}} //l u f
	};
	std::vector<Vertex> rightVec{
		{{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f}},//r u f //RIGHT FACE
		{{ 0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  1.0f}},//r u b
		{{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f}},//r b b
		{{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f}},//r b b
		{{ 0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  0.0f}},//r b f
		{{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f}} //r u f
	};
	std::vector<Vertex> bottomVec{
		{{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f,  1.0f}},//l b b //BOTTOM FACE
		{{ 0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f,  1.0f}},//r b b
		{{ 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f,  0.0f}},//r b f
		{{ 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f,  0.0f}},//r b f
		{{-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f,  0.0f}},//l b f
		{{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f,  1.0f}} //l b b
	};
	std::vector<Vertex> upVec{
		{{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f,  1.0f}},//l u b //UP FACE
		{{ 0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f,  1.0f}},//r u b
		{{ 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f,  0.0f}},//r u f
		{{ 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f,  0.0f}},//r u f
		{{-0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f,  0.0f}},//l u f
		{{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f,  1.0f}} //l u b
	};

	std::vector<std::vector<Vertex> > vecs;
	vecs.push_back(backVec);
	vecs.push_back(frontVec);
	vecs.push_back(leftVec);
	vecs.push_back(rightVec);
	vecs.push_back(bottomVec);
	vecs.push_back(upVec);
	std::vector<unsigned int> ind;
	for (unsigned int i = 0; i < 6; ++i)
		ind.push_back(i);
	static std::shared_ptr<Texture> dirt(new Texture("res/textures/dirt.png"));
	std::shared_ptr<Texture> grassSide(new Texture("res/textures/grassSide.png"));
	std::shared_ptr<Texture> grass(new Texture("res/textures/grass.png"));

	for (int i = 0; i < 6; ++i)
		dirtCube.push_back(std::unique_ptr<Mesh>(new Mesh(vecs[i], ind, dirt)));
		
	for(int i = 0; i < 4; ++i)
		grassCube.push_back(std::unique_ptr<Mesh>(new Mesh(vecs[i], ind, grassSide)));
	grassCube.push_back(std::unique_ptr<Mesh>(new Mesh(vecs[4], ind, dirt)));
	grassCube.push_back(std::unique_ptr<Mesh>(new Mesh(vecs[5], ind, grass)));
}