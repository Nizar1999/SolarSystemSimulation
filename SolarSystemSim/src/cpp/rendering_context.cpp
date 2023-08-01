#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "rendering_context.h"

namespace RenderingContext
{
	Shader* m_shader = nullptr;
	Shader* m_skyboxShader = nullptr;
	Shader* m_orbitShader = nullptr;

	Camera m_camera(glm::vec3(0.0f, 100.0f, 150.0f));

	unsigned int m_width;
	unsigned int m_height;

	GLFWwindow* m_window = nullptr;

	float m_deltaTime = 0.0f;
	bool m_focusGUI = false;
	float m_lastX;
	float m_lastY;

	namespace
	{
		float m_lastFrame = 0.0f;
		bool m_firstMouse = true;

		void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void errorCallback(int error, const char* description)
		{
			std::cerr << "GLFW Error: " << description << std::endl;
		}

		void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
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

		void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (m_focusGUI)
				return;
			m_camera.ProcessMouseScroll(yoffset);
		}
	}

	void initialize(unsigned int width, unsigned int height)
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

		setupGui();
	}

	void setupGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();
	}

	void updateDeltaTime()
	{
		auto currentFrame = static_cast<float>(glfwGetTime());
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
	}

	void cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete m_shader;
		delete m_skyboxShader;
		delete m_orbitShader;
		glfwTerminate();
	}
}

