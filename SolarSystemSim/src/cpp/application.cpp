#include "gui.h"
#include "input.h"
#include "configuration_view.h"

#include "application.h"


Application::Application(unsigned int width, unsigned int height)
{
	RenderingContext::initialize(width, height);
	m_solarSystem.initialize();
	m_skybox.initialize();
	Input::initializeInput();
	m_configurationController.bodies = &(m_solarSystem.m_bodies);
}

Application::~Application()
{
	RenderingContext::cleanup();
}

void Application::run()
{
	while (!glfwWindowShouldClose(RenderingContext::m_window))
	{
		auto scaledTime = static_cast<float>(glfwGetTime() * RenderingContext::m_timeScale);

		glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderingContext::updateDeltaTime();

		glfwPollEvents();

		Input::processInputPerFrame();

		m_solarSystem.update(scaledTime);
		m_skybox.update();

		if (RenderingContext::m_focusGUI)
		{
			Gui::beginGuiFrame();
			ConfigurationView::displayConfigurationOptions(m_configurationController.items, m_configurationController.selectedItem);
			ConfigurationView::addResetOrbitsButton(std::bind(&ConfigurationController::onResetOrbitsButtonClicked, &m_configurationController));
			m_configurationController.updateCameraMode();
			Gui::renderGuiFrame();
		}

		if (CelestialBody::activeBody)
		{
			RenderingContext::m_camera.setAttachedCameraView(CelestialBody::activeBody->getPosition(), m_solarSystem.m_bodies[0].getPosition(), RenderingContext::m_distanceFactor);
		}

		glfwSwapBuffers(RenderingContext::m_window);
	}
}
