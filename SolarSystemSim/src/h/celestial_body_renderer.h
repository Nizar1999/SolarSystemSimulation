#pragma once
#include "renderer_component.h"

class CelestialBodyRenderer
	: public RendererComponent
{
public:
	explicit CelestialBodyRenderer(TransformComponent* transform);
	void initialize() override;
	void update() override;

	bool lights = false;
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<float> m_normals;

	void generateSphereVertices(float radius, int slices, int stacks);
};

