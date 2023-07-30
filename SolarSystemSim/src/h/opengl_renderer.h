#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>
#include <map>

#include "camera.h"
#include "shader.h"
#include "celestial_body.h"

struct RenderingInfo
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int texture;
};

class OpenGLRenderer
{
public:
	OpenGLRenderer(unsigned int width, unsigned int height, const std::vector<CelestialBody*>& bodies);
	~OpenGLRenderer();

	void Run();


private:
	float m_timeScale = 0.1f;
	Shader* m_shader;

	std::vector<CelestialBody*> m_bodies;
	std::map<CelestialBody*, RenderingInfo> m_renderInfo;

	void initialize();
	void processInput();
	void update();
	void render();
	void cleanup();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void errorCallback(int error, const char* description);
	static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
#endif

