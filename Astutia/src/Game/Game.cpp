#include "Game.h"
#include "Renderer/Renderer.h"

std::vector<Event> Game::events;
std::vector< std::shared_ptr< Box > > Game::boxes;
Game::Game(){
	Box::init();
	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 25; ++j)
			boxes.push_back(std::shared_ptr< Box >(new Box(Box::grassCube, i - 12.5f, 0, j - 12.5f)));
	
	shader = std::shared_ptr<Shader>(new Shader());
}
void Game::update() {

	player.update(events);
	player.render(shader);

	for (auto& b : boxes)
		b->drawCubeMesh(shader);



	events.clear();

	skybox.draw(player.cam);
}
//IF NO COLLISION DETECTED, RETURNS A BOX AT Y -1000. IN GAME IT IS IMPOSSIBLE.
std::shared_ptr<Box> Game::collisionDetection(glm::vec3 pos) {
	for (std::shared_ptr<Box>& b : boxes)
		if (abs(b->getPos().x - pos.x) <= 0.5f && abs(b->getPos().y - pos.y) <= 0.5f &&
			abs(b->getPos().z - pos.z) <= 0.5f)
			return b;
	return std::shared_ptr<Box>(new Box(Box::dirtCube, 0, -10000, 0));
}
void Game::removeBox(std::shared_ptr<Box>& box) {
	for (auto it = boxes.begin(); it != boxes.end(); ++it)
		if ((*it)->getPos() == box->getPos()) {
			boxes.erase(it);
			break;
		}
}