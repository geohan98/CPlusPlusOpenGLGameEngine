#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "editorCameraController.h"
#include "Headers/cameras/camera3D.h"
#include "Headers/systems/inputPoller.h"
#include "Headers/systems/ButtonCodes.h"
#include "Headers/events/applicationEvents.h"

namespace Engine
{

	void EditorCameraController::init(float a, float b, float c, float d)
	{
		m_camera = std::shared_ptr<Camera>(new Camera3D(a, b, c, d));
		rot = glm::vec2(5, 0);
	}

	void EditorCameraController::onUpdate(float deltaTime)
	{
		if (Systems::InputPoller::isKeyPressed(KEY_W))
		{
			rot.x += deltaTime * m_turnSpeed;
		}
		if (Systems::InputPoller::isKeyPressed(KEY_S))
		{
			rot.x += deltaTime * -m_turnSpeed;
		}
		if (Systems::InputPoller::isKeyPressed(KEY_D))
		{
			rot.y += deltaTime * -m_turnSpeed;
		}
		if (Systems::InputPoller::isKeyPressed(KEY_A))
		{
			rot.y += deltaTime * m_turnSpeed;
		}

		glm::vec3 pos;
		glm::quat r = glm::angleAxis(glm::radians(rot.x), glm::vec3(1, 0, 0)) * glm::angleAxis(glm::radians(rot.y), glm::vec3(0, 1, 0)) * glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
		pos = glm::vec3(0, 0, -zoom) * r;


		m_camera->setPosition(pos);
		m_camera->setRotation(glm::vec3(rot.x, rot.y, 0));
		m_camera->update();
	}

	void EditorCameraController::onEvent(Events::Event& _e)
	{
		Events::EventDispatcher dispatcher(_e);
		dispatcher.dispatch<Events::WindowResize>(std::bind(&CameraController::resizeEvent, this, std::placeholders::_1));
	}

	bool EditorCameraController::resizeEvent(Events::WindowResize& e)
	{
		m_camera->resize(e.getWidth(), e.getHeight());
		return false;
	}

}