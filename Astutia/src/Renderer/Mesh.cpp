#include "Mesh.h"
#include "Renderer.h"
#include <iostream>
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
	std::shared_ptr<Texture>& diffuse_texture): diffuseTexture(diffuse_texture){
	std::shared_ptr<VertexBuffer> vbo(new VertexBuffer(&vertices[0],
		sizeof(Vertex) * vertices.size()));
	std::shared_ptr<IndexBuffer> ebo(new IndexBuffer(&indices[0], indices.size()));
	vbo->layout.push<float>(3);
	vbo->layout.push<float>(3);
	vbo->layout.push<float>(2);
	vao.reset(new VertexArray(vbo, ebo));
}

void Mesh::draw(const std::shared_ptr<Shader>& shader, int bindType) const {

	glBindTexture(bindType, diffuseTexture->getId());
	Renderer::renderer.render(shader, vao);
}