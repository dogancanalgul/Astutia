#pragma once
#include "Renderer/Shader.h"
#include <memory>
class Camera {
public:
	Camera(float x = 0.f, float y = 1.5f, float z = 0.f);

	void render(std::shared_ptr<Shader>& shader);
	void rotate(glm::vec2 offset);
	void move(glm::vec2 moveDir, bool canFly);

	void setPos(glm::vec3& pos);
	const glm::vec3& getPos() { return pos; }
	const glm::vec3& getFront() { return front; }
	void skyBoxView(std::shared_ptr<Shader>& shader) const;
private:
	void calculateMatrices();

	glm::vec3 pos;
	glm::vec3 up;
	glm::vec3 front;
	float fov;
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec2 yawPitch;
};