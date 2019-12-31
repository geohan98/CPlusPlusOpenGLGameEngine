#include "engine_pch.h"
#include "systems/log.h"
#include "cameras/camera2D.h"

namespace Engine
{

	Camera2D::Camera2D(float left, float right, float top, float bottom)
	{
		m_projection = glm::ortho(-10, 10, -10, 10);

		m_position = glm::vec3(0.0f, 0.0f, -10.0f);
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_view = rotationMatrix * translateMatrix;

		m_viewProjection = m_projection * m_view;
	}

	void Camera2D::update()
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_view = rotationMatrix * translateMatrix;

		m_viewProjection = m_projection * m_view;
	}

}