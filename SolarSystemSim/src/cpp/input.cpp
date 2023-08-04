#include "gui.h"

#include "input.h"

void Input::initializeInput()
{
	glfwSetKeyCallback(RenderingContext::m_window, processInput);
}

void Input::processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float deltaTime = RenderingContext::m_deltaTime;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_1:
			Gui::toggleDebugMenu();
			break;
		default:
			break;
		}
	}
}

void Input::processInputPerFrame()
{
	GLFWwindow* window = RenderingContext::m_window;
	Camera& camera = RenderingContext::m_camera;
	float deltaTime = RenderingContext::m_deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}
