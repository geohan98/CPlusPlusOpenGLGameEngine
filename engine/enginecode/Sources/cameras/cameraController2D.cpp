#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/cameras/cameraController2D.h"
#include "../enginecode/Headers/cameras/camera2D.h"

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