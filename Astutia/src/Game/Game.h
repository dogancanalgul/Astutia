#pragma once
#include <vector>
#include "Renderer/Shader.h"
#include <memory>
#include "Event.h"
#include "Player.h"
#include "Box.h"
#include "Skybox.h"
#include "World/World.h"
#define FIELDOFVIEW 65
//times 16 * 2 +1 == 33
// 32 * 2 + 1 == 65

class Game {
	friend class World;
public:
	Game();
	void update();

	static std::vector<Event> events;
	
	static std::shared_ptr<Box> collisionDetection(glm::vec3 pos);
	static void removeBox(std::shared_ptr<Box>& box);


	static float DELTATIME;
	static float LASTTIME;

private:
	void drawBoxes();
	static bool shouldDraw(glm::vec3 p1, glm::vec3 p2);

	std::shared_ptr<Shader> shader;

	//World can be at most 256 box in height
	//World Class will handle the boxes generation. Game Class will only be the glue in between.
	//When the player moves 1 Box forward the row at the farthest back will disappear while
	//another row is created in front.
	//In this system player can only see 16 boxes in front.
	static std::unique_ptr<World> world;
	
	Player player;
	Skybox skybox;
	
};