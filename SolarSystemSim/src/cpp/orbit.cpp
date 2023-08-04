#include "orbit.h"

#include <glm/gtc/constants.hpp>

Orbit::Orbit(nlohmann::json orbitInfo)
{
	m_orbitalParameters.semiMajorAxis = orbitInfo["semiMajorAxis"];
	m_orbitalParameters.eccentricity = orbitInfo["eccentricity"];
	m_orbitalParameters.inclination = orbitInfo["inclination"];
	m_orbitalParameters.longitudeOfAscendingNode = orbitInfo["longitudeOfAscendingNode"];
	m_orbitalParameters.argumentOfPeriapsis = orbitInfo["argumentOfPeriapsis"];

	addComponent<TransformComponent>();
	addComponent<OrbitRenderer>(getComponent<TransformComponent>());
}

void Orbit::update(float deltaTime)
{
	updateOrbitalCoordinates(deltaTime);
}

void Orbit::updateOrbitalCoordinates(float time)
{
	float meanAnomaly = 2.0f * glm::pi<float>() * time;  // Mean anomaly
	float eccentricAnomaly = meanAnomaly;                // Initial guess for eccentric anomaly

	// Iterate to solve for eccentric anomaly using Kepler's equation
	float tolerance = 0.0001f;                           // Tolerance for convergence
	int maxIterations = 100;                             // Maximum iterations
	for (int i = 0; i < maxIterations; ++i)
	{
		float nextEccentricAnomaly = eccentricAnomaly - (eccentricAnomaly - m_orbitalParameters.eccentricity * std::sin(eccentricAnomaly) - meanAnomaly) / (1.0f - m_orbitalParameters.eccentricity * std::cos(eccentricAnomaly));
		if (std::abs(nextEccentricAnomaly - eccentricAnomaly) < tolerance)
		{
			eccentricAnomaly = nextEccentricAnomaly;
			break;
		}
		eccentricAnomaly = nextEccentricAnomaly;
	}

	// Calculate true anomaly
	float trueAnomaly = 2.0f * std::atan(std::sqrt((1.0f + m_orbitalParameters.eccentricity) / (1.0f - m_orbitalParameters.eccentricity)) * std::tan(eccentricAnomaly / 2.0f));

	// Calculate distance from the focus (r)
	float distance = m_orbitalParameters.semiMajorAxis * (1.0f - m_orbitalParameters.eccentricity * std::cos(eccentricAnomaly));

	// Calculate position in orbital plane (x, y)
	float x = distance * (std::cos(m_orbitalParameters.longitudeOfAscendingNode) * std::cos(trueAnomaly + m_orbitalParameters.argumentOfPeriapsis) - std::sin(m_orbitalParameters.longitudeOfAscendingNode) * std::sin(trueAnomaly + m_orbitalParameters.argumentOfPeriapsis) * std::cos(m_orbitalParameters.inclination));
	float y = distance * (std::sin(m_orbitalParameters.longitudeOfAscendingNode) * std::cos(trueAnomaly + m_orbitalParameters.argumentOfPeriapsis) + std::cos(m_orbitalParameters.longitudeOfAscendingNode) * std::sin(trueAnomaly + m_orbitalParameters.argumentOfPeriapsis) * std::cos(m_orbitalParameters.inclination));

	// Calculate position in 3D space (x, y, z)
	float z = distance * std::sin(trueAnomaly + m_orbitalParameters.argumentOfPeriapsis) * std::sin(m_orbitalParameters.inclination);

	m_orbitalCoordinates = glm::vec3(x, z, y);
}

void Orbit::flushOrbitTrace()
{
	getComponent<OrbitRenderer>()->m_orbitTrace.clear();
}
