#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "rendering_context.h"

Shader* RenderingContext::m_shader = nullptr;
Shader* RenderingContext::m_skyboxShader = nullptr;
Shader* RenderingContext::m_orbitShader = nullptr;

Camera RenderingContext::m_camera(glm::vec3(0.0f, 100.0f, 150.0f));

unsigned int RenderingContext::m_width;
unsigned int RenderingContext::m_height;

GLFWwindow* RenderingContext::m_window = nullptr;

float RenderingContext::m_deltaTime = 0.0f;
float RenderingContext::m_lastFrame = 0.0f;

bool RenderingContext::m_firstMouse = true;
bool RenderingContext::m_focusGUI = false;
float RenderingContext::m_lastX;
float RenderingContext::m_lastY;

void RenderingContext::initialize(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_lastX = static_cast<float>(m_width) / 2.0f;
	m_lastY = static_cast<float>(m_height) / 2.0f;

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "OpenGL Renderer", nullptr, nullptr);
	if (!m_window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		cleanup();
	}
	glfwMakeContextCurrent(m_window);

	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_window, mouseCallback);
	glfwSetScrollCallback(m_window, scrollCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		cleanup();
	}

	m_shader = new Shader("./src/shaders/shader.vs", "./src/shaders/shader.fs");
	m_skyboxShader = new Shader("./src/shaders/shader_skybox.vs", "./src/shaders/shader_skybox.fs");
	m_orbitShader = new Shader("./src/shaders/shader.vs", "./src/shaders/shader_orbit.fs");

	glEnable(GL_DEPTH_TEST);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

void RenderingContext::updateDeltaTime()
{
	auto currentFrame = static_cast<float>(glfwGetTime());
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

void RenderingContext::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete m_shader;
	delete m_skyboxShader;
	delete m_orbitShader;
	glfwTerminate();
}

void RenderingContext::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void RenderingContext::errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void RenderingContext::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (m_focusGUI)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		return;
	}
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (m_firstMouse)
	{
		m_lastX = xpos;
		m_lastY = ypos;
		m_firstMouse = false;
	}

	float xoffset = xpos - m_lastX;
	float yoffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top
	m_lastX = xpos;
	m_lastY = ypos;

	m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void RenderingContext::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (m_focusGUI)
		return;
	m_camera.ProcessMouseScroll(yoffset);
}

