#include "gui.h"
#include "application.h"

Application::Application(unsigned int width, unsigned int height)
{
	RenderingContext::initialize(width, height);
	m_solarSystem.initialize();
	m_skybox.initialize();
}

Application::~Application()
{
	RenderingContext::cleanup();
}

void Application::run()
{
	std::vector<const char*> items = { "Free Cam", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
	int selectedItem = 0; // Index of the selected item (default: 0)

	while (!glfwWindowShouldClose(RenderingContext::m_window))
	{
		auto scaledTime = static_cast<float>(glfwGetTime() * RenderingContext::m_timeScale);

		glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderingContext::updateDeltaTime();

		glfwPollEvents();
		processInput();


		m_solarSystem.update(scaledTime);
		m_skybox.update();

		if (RenderingContext::m_focusGUI)
		{
			float k = 1.0f;
			Gui::beginGuiFrame();
			Gui::addSliderFloat("Camera Speed", &RenderingContext::m_camera.MovementSpeed, 0.0f, 100.0f);
			Gui::addSliderFloat("Time Scale", &RenderingContext::m_timeScale, 0.0f, 1.0f);
			Gui::addSliderFloat("Distance Factor", &RenderingContext::m_distanceFactor, 0.0f, 500.0f);
			Gui::addColorEdit("Orbit Color", glm::value_ptr(OrbitRenderer::m_color));
			Gui::addCombo("Camera Position", items, selectedItem);
			Gui::addCheckbox("Show Orbits", RenderingContext::m_renderOrbits);
			auto resetOrbits = [&]() {
				for (auto& body : m_solarSystem.m_bodies)
				{
					if (body.hasOrbit())
					{
						body.m_orbit->flushOrbitTrace();
					}

				}
			};
			Gui::addButton("Reset Orbits", resetOrbits);

			//TODO: refactor
			if (selectedItem != 0)
			{
				CelestialBody::activeBody = &(m_solarSystem.m_bodies[selectedItem]);
				RenderingContext::m_camera.attached = true;
			}
			else
			{
				CelestialBody::activeBody = nullptr;
				RenderingContext::m_camera.attached = false;
			}

			Gui::renderGuiFrame();
		}

		//TODO: fix
		if (CelestialBody::activeBody)
		{
			glm::vec3 celestialBodyPosition = CelestialBody::activeBody->getComponent<TransformComponent>()->m_position;
			glm::vec3 offset = glm::vec3(0.0f, 0.1f, -0.5f); // Example offset
			glm::vec3 cameraPosition = celestialBodyPosition + offset;
			// Calculate camera's target position (look toward the sun)
			glm::vec3 cameraTarget = celestialBodyPosition - m_solarSystem.m_bodies[0].getComponent<TransformComponent>()->m_position;
			glm::vec3 orbitalCoordinates = cameraPosition * RenderingContext::m_distanceFactor;
			RenderingContext::m_camera.vm = glm::lookAt(orbitalCoordinates, cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
			RenderingContext::m_camera.Position = orbitalCoordinates;
		}
		glfwSwapBuffers(RenderingContext::m_window);
	}
}

void Application::processInput()
{
	GLFWwindow* window = RenderingContext::m_window;
	Camera& camera = RenderingContext::m_camera;
	float deltaTime = RenderingContext::m_deltaTime;

	if (glfwGetKey(RenderingContext::m_window, GLFW_KEY_1) == GLFW_PRESS && !keyPressed)
	{
		keyPressed = true;

	}
	else if (keyPressed && glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
	{
		keyPressed = false;
		RenderingContext::m_focusGUI = !RenderingContext::m_focusGUI;
		if (!RenderingContext::m_focusGUI)
		{
			glfwSetCursorPos(window, RenderingContext::m_lastX, RenderingContext::m_lastY);
		}
		else
		{
			// Calculate the center position
			double centerX = static_cast<double>(RenderingContext::m_width) / 2.0;
			double centerY = static_cast<double>(RenderingContext::m_height) / 2.0;

			// Set the mouse position to the center of the window
			glfwSetCursorPos(window, centerX, centerY);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}
