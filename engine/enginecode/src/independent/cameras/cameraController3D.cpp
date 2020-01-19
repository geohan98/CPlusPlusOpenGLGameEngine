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

	void CameraController3D::onUpdate(float deltaTime)
	{
		//Forward
		if (Systems::InputPoller::isKeyPressed(KEY_W))
		{
			m_camera->setPosition(glm::vec4(m_camera->getPosition(), 0) + glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * m_camera->getView() * m_translateSpeed * deltaTime);
		}
		//Back
		if (Systems::InputPoller::isKeyPressed(KEY_S))
		{
			m_camera->setPosition(glm::vec4(m_camera->getPosition(), 0) + glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * m_camera->getView() * -m_translateSpeed * deltaTime);
		}
		//Right
		if (Systems::InputPoller::isKeyPressed(KEY_D))
		{
			m_camera->setPosition(glm::vec4(m_camera->getPosition(), 0) + glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * m_camera->getView() * -m_translateSpeed * deltaTime);
		}
		//Left
		if (Systems::InputPoller::isKeyPressed(KEY_A))
		{
			m_camera->setPosition(glm::vec4(m_camera->getPosition(), 0) + glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * m_camera->getView() * m_translateSpeed * deltaTime);
		}
		//Up
		if (Systems::InputPoller::isKeyPressed(KEY_SPACE))
		{
			m_camera->setPosition(glm::vec4(m_camera->getPosition(), 0) + glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * m_camera->getView() * -m_translateSpeed * deltaTime);
		}
		//Down
		if (Systems::InputPoller::isKeyPressed(KEY_LEFT_SHIFT))
		{
			m_camera->setPosition(glm::vec4(m_camera->getPosition(), 0) + glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * m_camera->getView() * m_translateSpeed * deltaTime);
		}

		if (Systems::InputPoller::isKeyPressed(KEY_RIGHT))
		{
			m_camera->setRotation(glm::vec4(m_camera->getRotation(), 0.0f) + (glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * m_camera->getView() * m_rotateSpeed * deltaTime));
		}

		if (Systems::InputPoller::isKeyPressed(KEY_LEFT))
		{
			m_camera->setRotation(glm::vec4(m_camera->getRotation(), 0.0f) + (glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * m_camera->getView() * -m_rotateSpeed * deltaTime));
		}

		if (Systems::InputPoller::isKeyPressed(KEY_UP))
		{
			m_camera->setRotation(glm::vec4(m_camera->getRotation(), 0.0f) + (glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * m_camera->getView() * m_rotateSpeed * deltaTime));
		}

		if (Systems::InputPoller::isKeyPressed(KEY_DOWN))
		{
			m_camera->setRotation(glm::vec4(m_camera->getRotation(), 0.0f) + (glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * m_camera->getView() * -m_rotateSpeed * deltaTime));
		}

		if (Systems::InputPoller::isKeyPressed(KEY_E))
		{
			m_camera->setRotation(glm::vec4(m_camera->getRotation(), 0.0f) + (glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * m_camera->getView() * m_rotateSpeed * deltaTime));
		}

		if (Systems::InputPoller::isKeyPressed(KEY_Q))
		{
			m_camera->setRotation(glm::vec4(m_camera->getRotation(), 0.0f) + (glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * m_camera->getView() * -m_rotateSpeed * deltaTime));
		}

		m_camera->update();
	}

}