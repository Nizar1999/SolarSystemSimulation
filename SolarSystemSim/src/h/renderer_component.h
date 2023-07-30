#pragma once

#include <string>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include "component.h"
#include "transform_component.h"
#include "rendering_context.h"

class RendererComponent
	: public Component
{
public:
	RendererComponent() = default;
	explicit RendererComponent(TransformComponent* transform);
	~RendererComponent() override;

	virtual void initialize() = 0;
	void update() override = 0;

	void setTexturePath(std::string_view texturePath);
	const std::string& getTexturePath() const;

protected:
	TransformComponent* m_transform = nullptr;
	std::string m_texturePath;

	struct PersistentRenderingInfo
	{
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		unsigned int texture;
	};
	PersistentRenderingInfo m_renderingInfo;
};

