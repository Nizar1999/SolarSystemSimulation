/*
 * Description: Performs initialization of different modules
 *				and orchestrates the main loop
 */

#pragma once

#include "rendering_context.h"
#include "skybox_renderer.h"
#include "solar_system.h"
#include "configuration_controller.h"

class Application
{
public:
	Application(unsigned int width, unsigned int height);
	~Application();
	void run();

private:
	SkyboxRenderer m_skybox;
	SolarSystem m_solarSystem;
	ConfigurationController m_configurationController;
};
