#include "renderer_component.h"

RendererComponent::RendererComponent(TransformComponent* transform)
	: m_transform(transform)
{
}

RendererComponent::~RendererComponent()
{
	glDeleteVertexArrays(1, &m_renderingInfo.VAO);
	glDeleteBuffers(1, &m_renderingInfo.VBO);
}

void RendererComponent::setTexturePath(std::string_view texturePath)
{
	m_texturePath = texturePath;
}

const std::string& RendererComponent::getTexturePath() const
{
	return m_texturePath;
}
