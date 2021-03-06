#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/cameras/camera2D.h"

namespace Engine
{

	Camera2D::Camera2D(float left, float right, float top, float bottom) : m_left(left),m_right(right),m_top(top),m_bottom(bottom)
	{
		m_projection = glm::ortho(m_left, m_right, m_bottom, m_top);

		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_view = translateMatrix;

		m_viewProjection = m_projection * m_view;
	}

	void Camera2D::update()
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_view = translateMatrix;

		m_viewProjection = m_projection * m_view;
	}

	void Camera2D::resize(float a, float b)
	{
		m_right = a;
		m_top = b;
		m_projection = glm::ortho(m_left, m_right, m_bottom, m_top);
	}

}