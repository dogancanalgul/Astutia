#include "Renderer.h"

	Renderer::Renderer(int width, int height) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, "Astutia", NULL, NULL);
		if (!window)
			glfwTerminate();

		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
	Renderer::~Renderer() {
		glfwDestroyWindow(window);
		glfwTerminate();
}
	void Renderer::clear(float r, float g, float b) const {
		glClearColor(r, g, b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
}
	void Renderer::render(const std::shared_ptr <Shader>& s, const std::shared_ptr<VertexArray>& vao) const {
		s->bind();
		vao->bind();
		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}
	void Renderer::swapBuffers() const{
		glfwSwapBuffers(window);
}