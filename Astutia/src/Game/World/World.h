#pragma once
#include "Game/Player.h"
#include <string>
#include "Game/Box.h"
#include <map>

class World {
public:

	World();
	~World();

	void update(Player& p);
	
	glm::vec3 worldCenter;
private:
	std::vector<Box> loadChunk(int x, int z, bool& loaded); 
	void saveChunk(int x, int z, std::vector<Box>& save);
	static std::vector<std::unique_ptr<Mesh>>& getType(char type);
	static char giveType(std::vector<std::unique_ptr<Mesh>>& type);
	
	std::map<std::string, std::string> worldMap;

	void loadMap();
	void saveMap();

	void movingLeft();
	void movingRight();
	void movingBack();
	void movingFront()
		
		;
	std::string saveName;

};

//World Save System:
//X-Z 0123456789:;<=>?@ABCD Z is end