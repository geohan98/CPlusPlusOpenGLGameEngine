#include "engine_pch.h"
#include "systems/log.h"
#include "core/freeOthographicCameraController2D.h"
#include "systems/inputPoller.h"
#include "systems/ButtonCodes.h"

namespace Engine
{

	FreeOthographicCameraController2D::FreeOthographicCameraController2D() {}

	void FreeOthographicCameraController2D::init(float left, float right, float width, float height)
	{
		m_camera = std::shared_ptr<OrthographicCamera2D>(new OrthographicCamera2D(left, height, width, height));
	}

	void FreeOthographicCameraController2D::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_W))
		{
			m_position.y += m_translateionSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_S))
		{
			m_position.y -= m_translateionSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_D))
		{
			m_position.x += m_translateionSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_A))
		{
			m_position.x -= m_translateionSpeed * timestep;
		}

		m_camera->setPositionRotation(m_position, m_rotation);
	}
}