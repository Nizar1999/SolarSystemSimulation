#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "camera.h"
#include "shader.h"

namespace RenderingContext
{
	extern Shader* m_shader;
	extern Shader* m_skyboxShader;
	extern Shader* m_orbitShader;
	extern Shader* m_sunShader;

	extern Camera m_camera;

	extern unsigned int m_width;
	extern unsigned int m_height;

	extern GLFWwindow* m_window;

	extern float m_deltaTime;
	extern bool m_focusGUI;
	extern float m_lastX;
	extern float m_lastY;

	void initialize(unsigned int width, unsigned int height);
	void updateDeltaTime();
	void cleanup();
	void setupGui();
};

