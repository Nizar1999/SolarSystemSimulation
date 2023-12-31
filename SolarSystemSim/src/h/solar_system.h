#pragma once

#include <vector>

#include "celestial_body.h"

class SolarSystem
{
public:
	SolarSystem();
	void initialize();
	void update(float scaledTime);

	std::vector<CelestialBody> m_bodies;
};

