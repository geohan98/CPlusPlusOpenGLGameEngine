#include "engine_pch.h"
#include "systems/log.h"
#include "cameras/cameraController2D.h"
#include "cameras/camera2D.h"

namespace Engine
{

	void CameraController2D::init(float a, float b, float c, float d)
	{
		m_camera = std::shared_ptr<Camera>(new Camera2D(a, b, c, d));
	}

	void CameraController2D::onUpdate(float deltaTime)
	{
		m_camera->update();
	}
}