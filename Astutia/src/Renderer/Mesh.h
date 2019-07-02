#pragma once
#include <memory>
#include <glm.hpp>
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};
class Mesh {
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices,
		std::shared_ptr<Texture>& diffuse_texture);
	void draw(const std::shared_ptr<Shader>& shader, int bindType = GL_TEXTURE_2D) const;
private:
	std::shared_ptr<VertexArray> vao;

	//Material
	//For now It only has a diffuseMap
	std::shared_ptr<Texture> diffuseTexture;

};