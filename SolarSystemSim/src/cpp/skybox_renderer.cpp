#include "skybox_renderer.h"

std::vector<std::string> SkyboxRenderer::m_faces = {
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"front.jpg",
	"back.jpg"
};

SkyboxRenderer::SkyboxRenderer(TransformComponent* transform)
	: RendererComponent(transform)
{
	transform->m_scale = { 1.0f, 1.0f, 1.0f };
}

void SkyboxRenderer::initialize()
{
	glGenVertexArrays(1, &m_renderingInfo.VAO);
	glGenBuffers(1, &m_renderingInfo.VBO);

	glBindVertexArray(m_renderingInfo.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderingInfo.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	loadTexture();

	RenderingContext::m_skyboxShader->use();
	RenderingContext::m_skyboxShader->setInt("skybox", 0);
}

void SkyboxRenderer::update()
{
	glDepthFunc(GL_LEQUAL);

	glm::mat4 projection = glm::perspective(glm::radians(RenderingContext::m_camera.Zoom), (float)RenderingContext::m_width / (float)RenderingContext::m_height, 0.1f, 10000.0f);

	RenderingContext::m_skyboxShader->use();
	RenderingContext::m_skyboxShader->setMat4("projection", projection);
	RenderingContext::m_skyboxShader->setMat4("view", glm::mat4(glm::mat3(RenderingContext::m_camera.GetViewMatrix())));

	glBindVertexArray(m_renderingInfo.VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderingInfo.texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

void SkyboxRenderer::loadTexture()
{
	glGenTextures(1, &m_renderingInfo.texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderingInfo.texture);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < m_faces.size(); i++)
	{
		unsigned char* data = stbi_load(("./resources/textures/" + m_faces[i]).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap failed to load at path: " << m_faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
