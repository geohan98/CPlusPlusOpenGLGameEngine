#include "engine_pch.h"
#include "systems/log.h"
#include "cameras/cameraController3D.h"
#include "cameras/camera3D.h"
#include "systems/inputPoller.h"
#include "systems/ButtonCodes.h"
namespace Engine
{

	void CameraController3D::init(float a, float b, float c, float d)
	{
		m_camera = std::shared_ptr<Camera>(new Camera3D(a, b, c, d));
	}

	void CameraController3D::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_W))
		{
			m_camera->setPosition(m_camera->getPosition() + (glm::vec3(0.0f, 0.0f, 1.0f) * m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_S))
		{
			m_camera->setPosition(m_camera->getPosition() + (glm::vec3(0.0f, 0.0f, 1.0f) * -m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_A))
		{
			m_camera->setPosition(m_camera->getPosition() + (glm::vec3(1.0f, 0.0f, 0.0f) * m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_D))
		{
			m_camera->setPosition(m_camera->getPosition() + (glm::vec3(1.0f, 0.0f, 0.0f) * -m_moveSpeed * timestep));
		}
		m_camera->update();
	}

	void CameraController3D::onEvent(Event& e)
	{

	}

	void CameraController3D::onResize()
	{

	}

}