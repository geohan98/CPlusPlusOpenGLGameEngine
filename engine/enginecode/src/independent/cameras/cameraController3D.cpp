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
			m_camera->setPosition(m_camera->getPosition() + (m_camera->m_forward * m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_S))
		{
			m_camera->setPosition(m_camera->getPosition() + (m_camera->m_forward * -m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_A))
		{
			m_camera->setPosition(m_camera->getPosition() + (m_camera->m_right * -m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_D))
		{
			m_camera->setPosition(m_camera->getPosition() + (m_camera->m_right * m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_SPACE))
		{
			m_camera->setPosition(m_camera->getPosition() + (m_camera->m_up * m_moveSpeed * timestep));
		}
		if (InputPoller::isKeyPressed(KEY_LEFT_SHIFT))
		{
			m_camera->setPosition(m_camera->getPosition() + (m_camera->m_up * -m_moveSpeed * timestep));
		}

		if (InputPoller::isKeyPressed(KEY_RIGHT))
		{
			m_camera->setRotation(m_camera->getRotation() + (glm::vec3(0.0f, 90.0f, 0.0f) * m_moveSpeed * timestep));
		}

		if (InputPoller::isKeyPressed(KEY_LEFT))
		{
			m_camera->setRotation(m_camera->getRotation() + (glm::vec3(0.0f, 90.0f, 0.0f) * -m_moveSpeed * timestep));
		}

		if (InputPoller::isKeyPressed(KEY_UP))
		{
			m_camera->setRotation(m_camera->getRotation() + (glm::vec3(90.0f, 0.0f, 0.0f) * m_moveSpeed * timestep));
		}

		if (InputPoller::isKeyPressed(KEY_DOWN))
		{
			m_camera->setRotation(m_camera->getRotation() + (glm::vec3(90.0f, 0.0f, 0.0f) * -m_moveSpeed * timestep));
		}

		if (InputPoller::isKeyPressed(KEY_E))
		{
			m_camera->setRotation(m_camera->getRotation() + (glm::vec3(0.0f, 0.0f, 90.0f) * m_moveSpeed * timestep));
		}

		if (InputPoller::isKeyPressed(KEY_Q))
		{
			m_camera->setRotation(m_camera->getRotation() + (glm::vec3(0.0f, 0.0f, 90.0f) * -m_moveSpeed * timestep));
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