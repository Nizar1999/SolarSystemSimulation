#pragma once

#include <string>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include <orbit.h>
#include <celestial_body_renderer.h>
#include <transform_component.h>
#include <entity.h>

class CelestialBody
	: public Entity
{
public:
	explicit CelestialBody(const std::string& name);

	void initialize();
	void update(float deltaTime) override;

	std::string getName() const
	{
		return m_name;
	}
	bool hasOrbit() const
	{
		return m_orbit != nullptr;
	}

	std::unique_ptr<Orbit> m_orbit;
private:
	//Config
	static nlohmann::json m_planetaryInformation;
	static nlohmann::json readPlanetaryInformationFile();

	//Properties
	std::string m_name;
	float m_rotationSpeed = 250.5f;

	void parsePlanetInfo(nlohmann::json& planetInfo);
	void initializeOrbit(nlohmann::json& planetInfo);
	void initializeWorldCoordinates(nlohmann::json& planetInfo);
	void updateRotationalAngle(float time);
};
