#include "Renderer.h"
#include "Game/Game.h"

Renderer Renderer::renderer;

float Renderer::DELTATIME = 0;
float Renderer::lastTime = 0;

double Renderer::SCREENWIDTH;
double Renderer::SCREENHEIGHT;

Renderer::Renderer(int width, int height) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		SCREENWIDTH = width;
		SCREENHEIGHT = height;
		window = glfwCreateWindow(width, height, "Astutia", NULL, NULL);
		if (!window)
			glfwTerminate();

		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		updateDelta();

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glEnable(GL_DEPTH_TEST);
		setMouseMovementCB();
		setMouseScrollCB();
		setMouseClickCB();
}
Renderer::~Renderer() {
		glfwDestroyWindow(window);
		glfwTerminate();
}
void Renderer::clear(float r, float g, float b) const {
		glClearColor(r, g, b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		updateDelta();
		processKeyInput();
	}
void Renderer::updateDelta() {
		DELTATIME = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
	}
void Renderer::render(const std::shared_ptr <Shader>& s, const std::shared_ptr<VertexArray>& vao) const {
		s->bind();
		vao->bind();
		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}
void Renderer::swapBuffers() const{
		glfwSwapBuffers(window);
}

void Renderer::setMouseMovementCB() const {
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double posX, double posY) {
		static double lastMousePos[2] = { Renderer::SCREENWIDTH / 2.f, Renderer::SCREENHEIGHT / 2.f };

		Game::events.push_back(Event(Event::Type::MOUSEMOVEMENT, posX - lastMousePos[0], lastMousePos[1] - posY));
		lastMousePos[0] = posX;
		lastMousePos[1] = posY;
	}
	);
}
void Renderer::setMouseScrollCB() const {
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
		Game::events.push_back(Event(Event::Type::MOUSESCROLL, xOffset, yOffset));
	}
	);
}
void Renderer::setMouseClickCB() const {
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			Game::events.push_back(Event(Event::Type::MOUSECLICK, 1, 0));
	});
}
void Renderer::processKeyInput() const {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Game::events.push_back(Event(Event::Type::PLAYERMOVEMENT, 0, 1));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Game::events.push_back(Event(Event::Type::PLAYERMOVEMENT, 0, -1));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Game::events.push_back(Event(Event::Type::PLAYERMOVEMENT, -1, 0));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Game::events.push_back(Event(Event::Type::PLAYERMOVEMENT, 1, 0));
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		Game::events.push_back(Event(Event::Type::PLAYERFLYTOGGLE, 0, 0));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Game::events.push_back(Event(Event::Type::PLAYERJUMP, 0, 0));
}
