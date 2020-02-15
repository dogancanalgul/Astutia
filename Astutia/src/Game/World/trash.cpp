
void World::movingLeft() {
	bool loaded = false;
	//Moving on -X
	//first move boxes	31 -> 32
	saveChunk(worldCenter.x + FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2, Game::boxes[FIELDOFVIEW - 1][0]);
	for (int i = FIELDOFVIEW - 1; i > 0; --i) {
		saveChunk(worldCenter.x + FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2 + i, Game::boxes[FIELDOFVIEW - 1][i]);
		for (int j = 0; j < FIELDOFVIEW - 1; ++j)
			Game::boxes[i][j] = Game::boxes[i - 1][j];
	}

	worldCenter.x -= 1;
	//then create a new row for boxes[0]
	int height = HEIGHT;
	for (int j = 0; j < FIELDOFVIEW; ++j) {
		loaded = false;
		Game::boxes[0][j] = loadChunk(worldCenter.x - FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2 + j, loaded);
		if (!loaded) {
			for (int k = 0; k < height; ++k)
				Game::boxes[0][j].push_back(Box(Box::grassCube, worldCenter.x - FIELDOFVIEW / 2, k, worldCenter.z - FIELDOFVIEW / 2 + j));
			saveChunk(worldCenter.x - FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2 + j, Game::boxes[0][j]);
		}
	}
}

void World::movingRight() {
	//Moving on +X
	//first move boxes	31 <- 32
	bool loaded = false;

	saveChunk(worldCenter.x - FIELDOFVIEW / 2, worldCenter.z + FIELDOFVIEW / 2, Game::boxes[0][FIELDOFVIEW - 1]);
	for (int i = 0; i < FIELDOFVIEW - 1; ++i) {
		saveChunk(worldCenter.x - FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2 + i, Game::boxes[0][i]);
		for (int j = 0; j < FIELDOFVIEW; ++j)
			Game::boxes[i][j] = Game::boxes[i + 1][j];
	}

	worldCenter.x += 1;
	//then create a new row for boxes[32]

	int height = HEIGHT;
	for (int j = 0; j < FIELDOFVIEW; ++j) {
		loaded = false;
		Game::boxes[FIELDOFVIEW - 1][j] = loadChunk(worldCenter.x + FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2 + j, loaded);
		if (!loaded) {
			for (int k = 0; k < height; ++k)
				Game::boxes[FIELDOFVIEW - 1][j].push_back(Box(Box::grassCube, worldCenter.x + FIELDOFVIEW / 2, k, worldCenter.z - FIELDOFVIEW / 2 + j));
			saveChunk(worldCenter.x + FIELDOFVIEW / 2, worldCenter.z - FIELDOFVIEW / 2 + j, Game::boxes[FIELDOFVIEW - 1][j]);
		}
	}
}

void World::movingFront() {
	//Moving on +Z
	//first move boxes	31 <- 32
	bool loaded = false;
	saveChunk(worldCenter.x + FIELDOFVIEW / 2, worldCenter.z + FIELDOFVIEW / 2, Game::boxes[FIELDOFVIEW - 1][0]);
	for (int i = 0; i < FIELDOFVIEW - 1; ++i) {
		saveChunk(worldCenter.x - FIELDOFVIEW / 2 + i, worldCenter.z - FIELDOFVIEW / 2, Game::boxes[i][0]);
		for (int j = 0; j < FIELDOFVIEW; ++j)
			Game::boxes[j][i] = Game::boxes[j][i + 1];
	}
	worldCenter.z += 1;
	//then create a new row for boxes[32]
	int height = HEIGHT;
	for (int j = 0; j < FIELDOFVIEW; ++j) {
		loaded = false;
		Game::boxes[j][FIELDOFVIEW - 1] = loadChunk(worldCenter.x - FIELDOFVIEW / 2 + j, worldCenter.z + FIELDOFVIEW / 2, loaded);
		if (!loaded) {
			for (int k = 0; k < height; ++k)
				Game::boxes[j][FIELDOFVIEW - 1].push_back(Box(Box::grassCube, worldCenter.x - FIELDOFVIEW / 2 + j, k, worldCenter.z + FIELDOFVIEW / 2));
			saveChunk(worldCenter.x - FIELDOFVIEW / 2 + j, worldCenter.z + FIELDOFVIEW / 2, Game::boxes[j][FIELDOFVIEW - 1]);
		}
	}
}

void World::movingBack() {
	bool loaded = false;
	//Moving on -Z
	//first move boxes	31 -> 32
	saveChunk(worldCenter.x - FIELDOFVIEW / 2, worldCenter.z + FIELDOFVIEW / 2, Game::boxes[0][FIELDOFVIEW - 1]);
	for (int i = FIELDOFVIEW - 1; i > 0; --i) {
		saveChunk(worldCenter.x - FIELDOFVIEW / 2 + i, worldCenter.z + FIELDOFVIEW / 2, Game::boxes[i][FIELDOFVIEW - 1]);
		for (int j = 0; j < FIELDOFVIEW; ++j)
			Game::boxes[j][i] = Game::boxes[j][i - 1];
	}

	worldCenter.z -= 1;
	//then create a new row for boxes[0]
	int height = HEIGHT;
	for (int j = 0; j < FIELDOFVIEW; ++j) {
		loaded = false;
		Game::boxes[j][0] = loadChunk(worldCenter.x - FIELDOFVIEW / 2 + j, worldCenter.z - FIELDOFVIEW / 2, loaded);
		if (!loaded) {
			for (int k = 0; k < height; ++k)
				Game::boxes[j][0].push_back(Box(Box::grassCube, worldCenter.x - FIELDOFVIEW / 2 + j, k, worldCenter.z - FIELDOFVIEW / 2));
			saveChunk(worldCenter.x - FIELDOFVIEW / 2 + j, worldCenter.z - FIELDOFVIEW / 2, Game::boxes[j][0]);
		}
	}
}

std::vector<std::unique_ptr<Mesh>>& World::getType(char type) {
	switch (type) {
	case '0':
	case '1':
		return Box::dirtCube;
	case '2':
		return Box::grassCube;
	}
}

char World::giveType(std::vector<std::unique_ptr<Mesh>>& type) {
	if (type == Box::dirtCube)
		return '1';
	else if (type == Box::grassCube)
		return '2';
}


void World::loadMap() {
	std::fstream f;
	std::string temp;
	int x, z;
	char trash;

	f.open(saveName, std::ios::in);
	//If there is no file create the file
	if (!f.is_open()) {
		f.open(saveName, std::ios::out);
		f << saveName << std::endl;
	}
	else {//If there is file read it.
		std::getline(f, temp);
		if (temp != saveName)
			std::cout << "Save File is corrupted for Loading.\n";

		while (std::getline(f, temp)) {
			std::stringstream stream(temp);
			std::stringstream coords("");

			stream >> x >> trash >> z >> trash;

			coords << x << "/" << z;
			worldMap.emplace(coords.str(), stream.str());
		}
	}
	f.close();
}

void World::saveMap() {
	std::fstream f;

	f.open(saveName, std::ios::out);
	f << saveName << std::endl;
	for (auto& it = worldMap.begin(); it != worldMap.end(); ++it)
		f << it->first << " " << it->second << std::endl;
}



void World::saveChunk(int x, int z, std::vector<Box>& save) {
	/*std::stringstream stream("");
	stream << x << "/" << z;
	std::string coord(stream.str());
	stream.str("");


	if (save.size() == 0)//If it is totally empty
		stream << '0';

	if (save.size() > 0 && save[0].getPos().y != 0)//If there is empty blocks in the bottom add them
		for(int i = 0; i < save[0].getPos().y; ++i)
			stream << '0';

	for (int i = 0; i < save.size(); ++i) {
		//If there is empty blocks in between write to file
		if (i != 0 && save[i].getPos().y - 1 != save[i - 1].getPos().y)
			for (int j = 0; j < save[0].getPos().y - save[i - 1].getPos().y - 1; ++j)
				stream << '0';
		stream << giveType(save[i].getType());
	}

	worldMap[coord] = stream.str();*/
}

std::vector<Box> World::loadChunk(int x, int z, bool& loaded) {
	std::stringstream stream("");
	stream << x << "/" << z;
	std::string coord(stream.str());
	std::vector<Box> box;

	for (auto it = worldMap.begin(); it != worldMap.end() && !loaded; ++it) {
		if (coord == it->first) {
			for (int i = 0; i < it->second.size(); ++i)
				if (it->second.at(i) != '0')
					box.push_back(Box(getType(it->second.at(i)), x, i, z));
			loaded = true;
		}
	}
	return box;
}