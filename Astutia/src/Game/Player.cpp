#include "Player.h"
#include "Game.h"

float Player::gravityForce = 0.00001f;

Player::Player() : inAir(false), isFlying(false), fallSpeed(0), fallAcc(0){
	//Intentionally left empty
}
void Player::update(std::vector<Event>& events) {

	if (!isFlying) {
		if (!inAir)
			checkInAir();
		if (inAir)
			fall();
	}
	else {
		fallSpeed = 0;
		fallAcc = 0;
		inAir = true;
	}
	
	for (Event event : events) {
		glm::vec2 info = event.getInfo();
		
		switch (event.getType()) {
		case Event::Type::MOUSEMOVEMENT:
			cam.rotate(info);
			break;
		case Event::Type::MOUSESCROLL:
			break;
		case Event::Type::PLAYERMOVEMENT:
			cam.move(info, isFlying);
			break;
		case Event::Type::PLAYERFLYTOGGLE:
			toggleFly();
			break;
		case Event::Type::PLAYERJUMP:
			if (!inAir)
				jump();
			break;
		case Event::Type::MOUSECLICK:
			boxSelection();
		}
	}
}
void Player::render(std::shared_ptr<Shader>& shader) {
	cam.render(shader);
}
void Player::checkInAir() {
	const std::shared_ptr<Box>& box = Game::collisionDetection(cam.getPos() + glm::vec3(0.f, -1.01f, 0.f));
	if (box->getPos().y == -10000)
		inAir = true;
}
void Player::fall() {
	glm::vec3 temp(cam.getPos());
	temp.y += fallSpeed * Game::DELTATIME;
	std::shared_ptr<Box> box = Game::collisionDetection(temp + glm::vec3(0.f, -1.01f, 0.f));
	if (box->getPos().y == -10000) {//Continues Falling
		if (fallSpeed >= -0.05f) {
			fallAcc -= gravityForce;
			fallSpeed += fallAcc;
		}
		cam.setPos(temp);
	}
	else {
		inAir = false;
		fallAcc = 0;
		fallSpeed = 0;
		cam.setPos(glm::vec3(temp.x, box->getPos().y + 1.51f, temp.z));
	}
}
void Player::jump() {
	fallSpeed = 0.04f;
	inAir = true;
}
void Player::boxSelection() {
	glm::vec3 rayDirection = cam.getFront();
	glm::vec3 rayPos = cam.getPos();
	for (float iteration = 0.05f; iteration <= 4.f; iteration += 0.05f) {
		std::shared_ptr<Box> box = Game::collisionDetection(rayPos + rayDirection * iteration);
		if (box->getPos().y != -10000) {
			Game::removeBox(box);
			break;
		}
	}
}