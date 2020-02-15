#include "Game.h"
#include "Renderer/Renderer.h"
#include "World/World.h"
#include <iostream>

std::vector<Event> Game::events;
std::vector<Box> Game::boxes[FIELDOFVIEW][FIELDOFVIEW];
std::unique_ptr<World> Game::world;

float Game::DELTATIME = 0;
float Game::LASTTIME = 0;

Game::Game(){
	Box::init();
	world = std::unique_ptr<World>(new World());
	shader = std::shared_ptr<Shader>(new Shader());
	LASTTIME = glfwGetTime();
}
void Game::update() {
	//UPDATE
	DELTATIME = LASTTIME - glfwGetTime();
	LASTTIME = glfwGetTime();
	player.update(events);
	world->update(player);

	//RENDER
	player.render(shader);
	drawBoxes();

	skybox.draw(player.cam);
	
	events.clear();
}
void Game::drawBoxes() {
	for (int i = 0; i < FIELDOFVIEW; ++i)
		for (int j = 0; j < FIELDOFVIEW; ++j)
			for (auto& b : boxes[i][j]) {
				if (shouldDraw(b.getPos(), player.cam.getPos()))
					b.drawCubeMesh(shader);
			}
}
bool Game::shouldDraw(glm::vec3 p1, glm::vec3 p2) {
	float difference= glm::length(p1 - p2);
	return -8 <= difference && difference <= 8;
}
//IF NO COLLISION DETECTED, RETURNS A BOX AT Y -1000. IN GAME IT IS IMPOSSIBLE.
std::shared_ptr<Box> Game::collisionDetection(glm::vec3 pos) {
	for (int i = 0; i < FIELDOFVIEW; ++i)
		for (int j = 0; j < FIELDOFVIEW; ++j)
			for (auto& b : boxes[i][j]) {
				if (abs(b.getPos().x - pos.x) <= 0.5f)
					break;
				if(abs(b.getPos().z - pos.z) <= 0.5f)
					break;
				if (abs(b.getPos().y - pos.y) <= 0.5f)
					return std::shared_ptr<Box>(new Box(b));
				else if (b.getPos().y > pos.y)
					break;
			}
	return std::shared_ptr<Box>(new Box(Box::dirtCube, 0, -10000, 0));
}
void Game::removeBox(std::shared_ptr<Box>& box) {
	glm::vec3 pos = box->getPos() - world->worldCenter;
	int x = pos.x + FIELDOFVIEW / 2;
	int z = pos.z + FIELDOFVIEW / 2;
	for (auto it = boxes[x][z].begin(); it != boxes[x][z].end(); ++it) {
		if (it->getPos() == box->getPos()) {
			boxes[x][z].erase(it);
			break;
		}
		else if (it->getPos().y > box->getPos().y)
			break;
	}
}