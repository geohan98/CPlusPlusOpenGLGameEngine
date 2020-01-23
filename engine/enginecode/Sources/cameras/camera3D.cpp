#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/cameras/camera3D.h"
#include "glm/gtx/rotate_vector.hpp"

namespace Engine
{

	Camera3D::Camera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

		m_position = glm::vec3(0.0f, 0.0f, -10.0f);
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		m_view = rotationMatrix * translateMatrix;

		m_viewProjection = m_projection * m_view;
	}

	void Camera3D::update()
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_view = rotationMatrix * translateMatrix;

		m_viewProjection = m_projection * m_view;
	}

}