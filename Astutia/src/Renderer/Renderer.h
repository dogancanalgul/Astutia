#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "Shader.h"

class Renderer {
public:
	Renderer(int width = 1024, int height = 768);
	~Renderer();

	void clear(float r = 0.1, float g = 0.f, float b = 0.3) const;
	void render(const std::shared_ptr <Shader>& s, const std::shared_ptr<VertexArray>& vao) const;
	void swapBuffers() const;
	
	inline bool isClosed() const { return glfwWindowShouldClose(window); }

	static Renderer renderer;
	static float DELTATIME;
	static double SCREENWIDTH;
	static double SCREENHEIGHT;

private:
	void static updateDelta();
	
	static float lastTime;
	GLFWwindow* window;
	
	//CALLBACKS
	void setMouseMovementCB() const;
	void setMouseScrollCB() const;
	void processKeyInput() const;
	void setMouseClickCB() const;
};