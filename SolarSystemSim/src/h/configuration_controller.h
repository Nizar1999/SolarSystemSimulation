#pragma once

#include <vector>

#include "celestial_body.h"

class ConfigurationController
{
public:

	void updateCameraMode()
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

	void onResetOrbitsButtonClicked()
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

	//TODO: make private
	std::vector<CelestialBody>* bodies;
	std::vector<const char*> items = { "Free Cam", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
	int selectedItem = 0; // Index of the selected item (default: 0)
};

