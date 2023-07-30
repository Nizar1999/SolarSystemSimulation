#include "celestial_body.h"
#include <fstream>
#include <iostream>

nlohmann::json CelestialBody::m_planetaryInformation = CelestialBody::readPlanetaryInformationFile();

CelestialBody::CelestialBody(const std::string& name)
	: m_name(name)
{
	addComponent<TransformComponent>();
	addComponent<CelestialBodyRenderer>(getComponent<TransformComponent>());

	parsePlanetInfo(m_planetaryInformation["celestialBody"][name]);
}

void CelestialBody::initialize()
{
	getComponent<CelestialBodyRenderer>()->initialize();
}

void CelestialBody::parsePlanetInfo(nlohmann::json& planetInfo)
{
	if (planetInfo.empty())
	{
		std::cerr << "Could not find planet in config file\n";
		return;
	}

	getComponent<CelestialBodyRenderer>()->setTexturePath(planetInfo["texture"]);
	getComponent<TransformComponent>()->m_scale = glm::vec3(planetInfo["scale"]);

	initializeWorldCoordinates(planetInfo);
	initializeOrbit(planetInfo);
}

void CelestialBody::initializeWorldCoordinates(nlohmann::json& planetInfo)
{
	getComponent<TransformComponent>()->m_world =
	{ planetInfo["position"]["x"],
		planetInfo["position"]["y"],
		planetInfo["position"]["z"] };
}

void CelestialBody::initializeOrbit(nlohmann::json& planetInfo)
{
	nlohmann::json orbitInfo = planetInfo["orbitParameters"];
	if (!orbitInfo.empty())
	{
		m_orbit = std::make_unique<Orbit>(orbitInfo);
	}
}

void CelestialBody::update(float deltaTime)
{
	TransformComponent* transform = getComponent<TransformComponent>();
	updateRotationalAngle(deltaTime);
	if (hasOrbit())
	{
		m_orbit->update(deltaTime);
		transform->m_position = m_orbit->getOrbitalCoordinates();

		float distanceFactor = 20.0f;
		auto model = glm::mat4(1.0f);

		model = glm::translate(model, transform->m_world);
		glm::vec3 orbitalCoordinates = transform->m_position * (distanceFactor / 2);

		model = glm::translate(model, orbitalCoordinates);
		model = glm::rotate(model, transform->m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, transform->m_scale);

		m_orbit->updateOrbitTrace(glm::vec3(model[3]));
	}

	getComponent<CelestialBodyRenderer>()->update();
	if (hasOrbit())
	{
		m_orbit->getComponent<OrbitRenderer>()->update();
	}
}

void CelestialBody::updateRotationalAngle(float time)
{
	getComponent<TransformComponent>()->m_rotation = time * glm::radians(m_rotationSpeed);
}

nlohmann::json CelestialBody::readPlanetaryInformationFile()
{
	std::ifstream file("./resources/config.json");
	if (!file.is_open())
	{
		std::cerr << "Failed to open planetary information file\n";
		return "";
	}

	std::string jsonData((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	return nlohmann::json::parse(jsonData);
}
