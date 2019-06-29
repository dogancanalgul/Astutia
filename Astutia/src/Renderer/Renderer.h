#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "Shader.h"

class Renderer {
public:
	Renderer(int width = 640, int height = 480);
	~Renderer();

	void clear(float r = 0.1, float g = 0.f, float b = 0.3) const;
	void render(const std::shared_ptr <Shader>& s, const std::shared_ptr<VertexArray>& vao) const;
	void swapBuffers() const;

	inline bool isClosed() const { return glfwWindowShouldClose(window);  }
private:
	GLFWwindow* window;

};