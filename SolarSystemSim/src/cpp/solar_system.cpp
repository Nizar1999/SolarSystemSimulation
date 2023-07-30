#include "solar_system.h"

SolarSystem::SolarSystem()
{
}

void SolarSystem::initialize()
{
	m_bodies.emplace_back("Sun");
	m_bodies.emplace_back("Mercury");
	m_bodies.emplace_back("Venus");
	m_bodies.emplace_back("Earth");
	m_bodies.emplace_back("Mars");
	m_bodies.emplace_back("Jupiter");
	m_bodies.emplace_back("Saturn");
	m_bodies.emplace_back("Uranus");
	m_bodies.emplace_back("Neptune");

	for (auto& body : m_bodies)
	{
		body.initialize();
	}
}

void SolarSystem::update(float scaledTime)
{
	for (auto& body : m_bodies)
	{
		body.update(scaledTime);
	}
}
