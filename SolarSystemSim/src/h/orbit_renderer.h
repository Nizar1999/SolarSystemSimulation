#pragma once

#include <vector>

#include "renderer_component.h"

class OrbitRenderer
	: public RendererComponent
{
public:
	explicit OrbitRenderer(TransformComponent* transform);
	void initialize() override;
	void update() override;

	std::vector<float> m_orbitTrace;
	static glm::vec4 m_color;
};
