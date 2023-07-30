#pragma once
#include "component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class TransformComponent :
	public Component
{
public:
	~TransformComponent() = default;
	void update()
	{
	};
	glm::vec3 m_world;
	glm::vec3 m_position;
	float m_rotation;
	glm::vec3 m_scale;
};

