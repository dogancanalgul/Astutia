#include "Camera.h"
#include "Renderer/Renderer.h"
#include<gtc/matrix_transform.hpp>

Camera::Camera(float x, float y, float z) : pos(glm::vec3(x, y, z)),
	up(glm::vec3(0.f, 1.f, 0.f)), front(glm::vec3(0.f, 0.f, -1.f)), fov(60.f){
	calculateMatrices();
	yawPitch = glm::vec2(270.f, 0.f);
}

void Camera::render(std::shared_ptr<Shader>& shader) {
	shader->bind();
	shader->setUniformMatrix4f("view", view);
	shader->setUniformMatrix4f("projection", projection);
}
void Camera::skyBoxView(std::shared_ptr<Shader>& shader) const{
	shader->bind();
	shader->setUniformMatrix4f("view", glm::mat4(glm::mat3(view)));
	shader->setUniformMatrix4f("projection", projection);
}


void Camera::calculateMatrices() {
	view = glm::lookAt(pos, pos + front, up);
	projection = glm::perspective(glm::radians(fov), (float)Renderer::SCREENWIDTH/ (float)Renderer::SCREENHEIGHT, 0.1f, 100.0f);
}
void Camera::rotate(glm::vec2 offset) {

	double sensitivity = 0.05f;
	offset *= sensitivity;
	yawPitch += offset;
	if (yawPitch.y > 89.f)
		yawPitch.y = 89.f;
	else if (yawPitch.y < -89.f)
		yawPitch.y = -89.f;
	front.x = cos(glm::radians(yawPitch.y)) * cos(glm::radians(yawPitch.x));
	front.y = sin(glm::radians(yawPitch.y));
	front.z = cos(glm::radians(yawPitch.y)) * sin(glm::radians(yawPitch.x));
	front = glm::normalize(front);
	calculateMatrices();
}

void Camera::move(glm::vec2 moveDir, bool canFly) {
	float speed = 5.f * Renderer::DELTATIME;

	float yCoord = pos.y;//To prevent flying
	
	if (moveDir.x == 1) 
			pos += glm::normalize(glm::cross(front, up)) * speed;
	else if(moveDir.x == -1)
			pos -= glm::normalize(glm::cross(front, up)) * speed;
	else if (moveDir.y == 1)
			pos += front * speed;
	else if(moveDir.y == -1)
			pos -= front * speed;

	if (!canFly)
		pos.y = yCoord;

	calculateMatrices();
}

void Camera::setPos(glm::vec3& pos) {
	this->pos = pos;  
	calculateMatrices(); 
}