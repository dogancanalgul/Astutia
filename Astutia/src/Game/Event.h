#pragma once
#include <glm.hpp>

class Event {
public:
	enum class Type {
		None = 0,
		MOUSEMOVEMENT,
		MOUSESCROLL,
		PLAYERMOVEMENT,
		PLAYERFLYTOGGLE,
		PLAYERJUMP,
		MOUSECLICK
	};

	Event(Type type, double v1, double v2);

	const glm::vec2 getInfo() const{ return info; }
	Type getType() { return type; }
	void handled() { is_handled = true; }
	bool isHandled() { return is_handled; }
private:
	Type type;
	glm::vec2 info;
	bool is_handled;

};