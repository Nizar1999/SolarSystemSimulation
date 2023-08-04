#pragma once

#include <vector>

#include "celestial_body.h"

class ConfigurationController
{
public:
	void updateCameraMode();
	void onResetOrbitsButtonClicked();

	//TODO: make private
	std::vector<CelestialBody>* bodies;
	std::vector<const char*> items = { "Free Cam", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
	int selectedItem = 0; // Index of the selected item (default: 0)
};

