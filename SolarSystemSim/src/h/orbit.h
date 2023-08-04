#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include <entity.h>
#include <orbit_renderer.h>
#include <transform_component.h>

class Orbit
	: public Entity
{
public:
	Orbit(nlohmann::json orbitInfo);
	void update(float deltaTime) override;

	void updateOrbitalCoordinates(float time);
	void flushOrbitTrace();
	glm::vec3 getOrbitalCoordinates() const
	{
		return m_orbitalCoordinates;
	}
	void updateOrbitTrace(glm::vec3 coordinates)
	{
		std::vector<float>& orbitTrace = getComponent<OrbitRenderer>()->m_orbitTrace;
		orbitTrace.push_back(coordinates.x);
		orbitTrace.push_back(coordinates.y);
		orbitTrace.push_back(coordinates.z);
	}

private:
	struct OrbitalParameters
	{
		float semiMajorAxis;              // Semi-major axis of the orbit
		float eccentricity;               // Eccentricity of the orbit
		float inclination;                // Inclination of the orbit
		float longitudeOfAscendingNode;   // Longitude of the ascending node
		float argumentOfPeriapsis;        // Argument of periapsis
	};

	OrbitalParameters m_orbitalParameters;
	glm::vec3 m_orbitalCoordinates;
};

