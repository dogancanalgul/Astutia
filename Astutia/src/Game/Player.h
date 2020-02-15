#pragma once
#include "Event.h"
#include "Camera.h"
#include <vector>

class Player {
	friend class Game;
	friend class World;
public:
	Player();
	void update(std::vector<Event>& events);
	void render(std::shared_ptr<Shader>& shader);
protected:
	void toggleFly() { isFlying = !isFlying; }
	void checkInAir();
	void fall();
	void jump();
	void boxSelection();//IN ALPHA IT WILL DELETE ANYTHING YOU LEFT CLICK


	bool inAir = false;
	bool isFlying = false;
	static float gravityForce;
	float fallSpeed;
	float fallAcc;

	Camera cam;//Player will use cam position.
};