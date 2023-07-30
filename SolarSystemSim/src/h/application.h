#pragma once

#include "rendering_context.h"
#include "skybox_renderer.h"
#include "solar_system.h"

class Application
{
public:
	Application(unsigned int width, unsigned int height);
	void run();

private:
	SkyboxRenderer m_skybox;
	bool keyPressed = false;
	SolarSystem m_solarSystem;
	float m_timeScale = 0.1f;

	void processInput();
};

