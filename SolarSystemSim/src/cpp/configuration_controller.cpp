#include "configuration_controller.h"

void ConfigurationController::updateCameraMode()
{
	if (selectedItem != 0)
	{
		CelestialBody::activeBody = &((*bodies)[selectedItem]);
		RenderingContext::m_camera.attached = true;
	}
	else
	{
		CelestialBody::activeBody = nullptr;
		RenderingContext::m_camera.attached = false;
	}
}

void ConfigurationController::onResetOrbitsButtonClicked()
{
	if (bodies == nullptr) { return; }
	for (auto& body : *bodies)
	{
		if (body.hasOrbit())
		{
			body.m_orbit->flushOrbitTrace();
		}

	}
}
