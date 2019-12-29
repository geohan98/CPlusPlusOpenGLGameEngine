#include "engine_pch.h"
#include "systems/log.h"
#include "cameras/camera3D.h"
#include "glm/gtx/rotate_vector.hpp"

namespace Engine
{

	Camera3D::Camera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_position = glm::vec3(0.0f, 0.0f, -5.0f);
		m_rotation = glm::vec3(0.0f, 90.0f, 0.0f);
		m_view = glm::lookAt(m_position, m_position + forward, up);

		m_viewProjection = m_projection * m_view;
	}

	void Camera3D::update()
	{
		m_forward = glm::vec3(0.0f, 0.0f, 1.0f);

		m_forward.x = m_forward.x * cos(glm::radians(m_rotation.y)) - m_forward.z * sin(glm::radians(m_rotation.y));
		m_forward.z = m_forward.z * cos(glm::radians(m_rotation.y)) + m_forward.x * sin(glm::radians(m_rotation.y));


		m_right = glm::vec3(1.0f, 0.0f, 0.0f);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);

		m_view = glm::lookAt(m_position, m_position + m_forward, m_up);

		m_viewProjection = m_projection * m_view;
	}

}