#include "celestial_body_renderer.h"
CelestialBodyRenderer::CelestialBodyRenderer(TransformComponent* transform)
	: RendererComponent(transform)
{
	generateSphereVertices(1.0f, 60, 60);
}

void CelestialBodyRenderer::initialize()
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int normalsVBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &normalsVBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(float), m_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//TODO: inject the shader instead
	if (lights)
	{
		RenderingContext::m_sunShader->use();
	}
	else
	{
		RenderingContext::m_shader->use();
	}
	glEnable(GL_DEPTH_TEST);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width;
	int height;
	int nrChannels;

	unsigned char* data = stbi_load(m_texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//TODO: inject the shader instead
	if (lights)
	{
		RenderingContext::m_sunShader->setInt("SurfaceTex", 0);
	}
	else
	{
		RenderingContext::m_shader->setInt("SurfaceTex", 0);
	}

	m_renderingInfo = { VAO, VBO, normalsVBO, EBO, texture };

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CelestialBodyRenderer::update()
{
	glBindVertexArray(m_renderingInfo.VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_renderingInfo.texture);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glm::mat4 projection = glm::perspective(glm::radians(RenderingContext::m_camera.Zoom), (float)RenderingContext::m_width / (float)RenderingContext::m_height, 0.1f, 10000.0f);

	auto model = glm::mat4(1.0f);

	model = glm::translate(model, m_transform->m_world);

	// Update model matrix with orbital coordinates, orbital rotation and planetary scale
	float distanceFactor = 20.0f;
	glm::vec3 orbitalCoordinates = m_transform->m_position * (distanceFactor / 2);

	model = glm::translate(model, orbitalCoordinates);
	model = glm::rotate(model, m_transform->m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, m_transform->m_scale);


	//TODO: inject shader
	if (lights)
	{
		RenderingContext::m_sunShader->use();
		RenderingContext::m_sunShader->setMat4("projection", projection);
		RenderingContext::m_sunShader->setMat4("view", RenderingContext::m_camera.GetViewMatrix());
		RenderingContext::m_sunShader->setMat4("model", model);
	}
	else
	{
		RenderingContext::m_shader->use();
		RenderingContext::m_shader->setVec3("objectColor", { 1.0f, 1.0f, 1.0f });
		RenderingContext::m_shader->setVec3("lightColor", { 1.0f, 1.0f, 1.0f });
		RenderingContext::m_shader->setVec3("lightPos", { 0.0f, 0.0f, 0.0f }); //TODO: give it the actual position of the sun

		RenderingContext::m_shader->setMat4("projection", projection);
		RenderingContext::m_shader->setMat4("view", RenderingContext::m_camera.GetViewMatrix());
		RenderingContext::m_shader->setMat4("model", model);
	}

	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CelestialBodyRenderer::generateSphereVertices(float radius, int slices, int stacks)
{
	for (int i = 0; i <= stacks; ++i)
	{
		float phi = static_cast<float>(i) / stacks * glm::pi<float>();  // Vertical angle
		float sinPhi = std::sin(phi);
		float cosPhi = std::cos(phi);

		for (int j = 0; j <= slices; ++j)
		{
			float theta = static_cast<float>(j) / slices * 2 * glm::pi<float>();  // Horizontal angle
			float sinTheta = std::sin(theta);
			float cosTheta = std::cos(theta);

			float x = cosTheta * sinPhi;
			float y = cosPhi;
			float z = sinTheta * sinPhi;

			float u = static_cast<float>(j) / slices;    // Texture coordinate u
			float v = static_cast<float>(i) / stacks;

			m_vertices.push_back(radius * x);
			m_vertices.push_back(radius * y);
			m_vertices.push_back(radius * z);

			m_normals.push_back(x);
			m_normals.push_back(y);
			m_normals.push_back(z);

			m_vertices.push_back(u);
			m_vertices.push_back(v);
		}

		for (unsigned int i = 0; i < stacks; ++i)
		{
			unsigned int startIndex = i * (slices + 1);
			unsigned int nextRowStartIndex = (i + 1) * (slices + 1);

			for (unsigned int j = 0; j < slices; ++j)
			{
				m_indices.push_back(startIndex + j);
				m_indices.push_back(nextRowStartIndex + j);
				m_indices.push_back(startIndex + j + 1);

				m_indices.push_back(nextRowStartIndex + j);
				m_indices.push_back(nextRowStartIndex + j + 1);
				m_indices.push_back(startIndex + j + 1);
			}
		}
	}
}
