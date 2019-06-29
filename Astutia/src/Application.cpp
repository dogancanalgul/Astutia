#include "Renderer/Renderer.h"
#include <memory>
int main(){
	Renderer renderer;

	float vertices[] = {
		-0.5f, -0.5f, 0.1f,
		 0.5f, -0.5f, 0.1f,
		-0.5f,  0.5f, 0.1f,
		 0.5f,  0.5f, 0.1f
	};
	unsigned int indices[] = { 0, 1, 2, 2, 1, 3};

	std::shared_ptr <Shader> shader(new Shader());
	std::shared_ptr< VertexBuffer> vbo( new VertexBuffer(vertices,  sizeof(vertices)));
	vbo->layout.push<float>(3);
	std::shared_ptr< IndexBuffer> ib( new IndexBuffer(indices, 6));
	std::shared_ptr<VertexArray> vao( new VertexArray(vbo, ib));

	while (!renderer.isClosed()){
		glfwPollEvents();

		renderer.clear();
		renderer.render(shader, vao);
		renderer.swapBuffers();
	}
	return 0;
}