#include "engine_pch.h"
#include "systems/log.h"
#include "core/perspectiveCameraController.h"

namespace Engine
{

	void PerspectiveCameraController::updateView()
	{

	}

	PerspectiveCameraController::PerspectiveCameraController()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward = glm::normalize(forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));

		m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	void PerspectiveCameraController::init(float a, float b, float c, float d)
	{
		m_camera = std::make_shared<PerspectiveCamera3D>(PerspectiveCamera3D(a, b, c, d));
	}

	std::shared_ptr<Camera> PerspectiveCameraController::getCamera()
	{
		return m_camera;
	}

	void PerspectiveCameraController::onUpdate(float timestep)
	{
		m_camera->setPosition(m_position);
		m_camera->setOrientation()
	}

	void PerspectiveCameraController::onEvent(Event& e)
	{

	}

	void PerspectiveCameraController::onResize()
	{

	}

	bool PerspectiveCameraController::onMouseButton(MouseButtonPressed& e)
	{

	}

}