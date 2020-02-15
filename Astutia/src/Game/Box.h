#pragma once
#include <glm.hpp>
#include <memory>
#include "Renderer/Mesh.h"

class Box {
public:
	Box(std::vector<std::unique_ptr<Mesh>>& cubeType = dirtCube,float x = 0, float y = 0, float z = 0);

	//For model matrix
	void setPos(glm::vec3 Position);
	void move(glm::vec3 offset);

	void rotate(glm::vec3 RotateAxis, float RotateDegree);
	void scale(float Scale);

	glm::mat4 getModelMatrix() const {return modelMatrix; }

	glm::vec3 getPos() { return pos; }
	float getScale() const { return scaleAll; }
	glm::vec3 getRotationAxis() const { return rotationAxis; }
	float getRotationDegree() const { return rotationDegree; }
	std::vector<std::unique_ptr<Mesh>>& getType() { return *type; }

	void drawCubeMesh(std::shared_ptr<Shader>& shader);
	static void init();

	static std::vector<std::unique_ptr<Mesh>> dirtCube;
	static std::vector<std::unique_ptr<Mesh>> grassCube;
private:
	void calculateMatrix();
	std::vector<std::unique_ptr<Mesh>>* type;
	glm::mat4 modelMatrix;
	glm::vec3 pos;
	float scaleAll;
	glm::vec3 rotationAxis;
	float rotationDegree;
};
