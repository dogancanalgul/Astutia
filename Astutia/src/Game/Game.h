#pragma once
#include <vector>
#include "Renderer/Shader.h"
#include <memory>
#include "Event.h"
#include "Player.h"
#include "Box.h"
#include "Skybox.h"

class Game {
public:
	Game();
	void update();

	static std::vector<Event> events;
	
	static std::shared_ptr<Box> collisionDetection(glm::vec3 pos);
	static void removeBox(std::shared_ptr<Box>& box);
private:
	std::shared_ptr<Shader> shader;
	static std::vector < std::shared_ptr< Box > > boxes;//It is used for Collision Detection
	Player player;
	Skybox skybox;
	
};
