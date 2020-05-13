#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "Headers/cameras/cameraController2D.h"
#include "Headers/cameras/camera2D.h"
#include "Headers/events/applicationEvents.h"

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

	void CameraController2D::onEvent(Events::Event& _e)
	{
		Events::EventDispatcher dispatcher(_e);
		dispatcher.dispatch<Events::WindowResize>(std::bind(&CameraController::resizeEvent, this, std::placeholders::_1));
	}

	bool CameraController2D::resizeEvent(Events::WindowResize& e)
	{
		m_camera->resize(e.getWidth(), e.getHeight());
		return false;
	}
}