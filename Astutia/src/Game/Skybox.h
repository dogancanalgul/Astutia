#pragma once
#include <memory>
#include "Renderer/Shader.h"
#include "Camera.h"

class Skybox {
public:
	Skybox();

	void draw(const Camera& cam);
private:
	void loadMap();
	void bindVertices();

	std::shared_ptr< Shader > shader;
	unsigned int vao, texID;

	
};