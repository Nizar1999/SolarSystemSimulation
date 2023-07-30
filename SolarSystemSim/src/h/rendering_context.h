#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "shader.h"

class RenderingContext
{
public:
	static void initialize(unsigned int width, unsigned int height);
	static void updateDeltaTime();
	static void cleanup();

	static Shader* m_shader;
	static Shader* m_skyboxShader;
	static Shader* m_orbitShader;
	static Camera m_camera;
	static unsigned int m_width;
	static unsigned int m_height;

	static GLFWwindow* m_window;
	static float m_deltaTime;
	static bool m_focusGUI;
	static float m_lastX;
	static float m_lastY;

private:
	static float m_lastFrame;
	static bool m_firstMouse;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void errorCallback(int error, const char* description);
	static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

