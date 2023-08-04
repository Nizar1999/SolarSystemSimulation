#include "orbit_renderer.h"

glm::vec4 OrbitRenderer::m_color = { 0.45f, 0.45f, 0.45f, 0.45f };

OrbitRenderer::OrbitRenderer(TransformComponent* transform)
	: RendererComponent(transform)
{
	initialize();
}

void OrbitRenderer::initialize()
{
	glGenVertexArrays(1, &m_renderingInfo.VAO);
	glGenBuffers(1, &m_renderingInfo.VBO);
}

void OrbitRenderer::update()
{
	if (!RenderingContext::m_renderOrbits)
	{
		return;
	}
	glBindVertexArray(m_renderingInfo.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderingInfo.VBO);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBufferData(GL_ARRAY_BUFFER, m_orbitTrace.size() * sizeof(float), m_orbitTrace.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glm::mat4 projection = glm::perspective(glm::radians(RenderingContext::m_camera.Zoom), (float)RenderingContext::m_width / (float)RenderingContext::m_height, 0.1f, 10000.0f);

	RenderingContext::m_orbitShader->use();
	RenderingContext::m_orbitShader->setMat4("projection", projection);
	RenderingContext::m_orbitShader->setMat4("view", RenderingContext::m_camera.GetViewMatrix());
	RenderingContext::m_orbitShader->setMat4("model", glm::mat4(1.0f));
	RenderingContext::m_orbitShader->setVec4("Color", m_color);

	glDrawArrays(GL_LINE_STRIP, 0, m_orbitTrace.size());

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
