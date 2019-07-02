#include "Event.h"

Event::Event(Type type, double v1, double v2) :type(type), info(glm::vec2(v1,v2))
, is_handled(false){
	//Intentionally left empty
}
