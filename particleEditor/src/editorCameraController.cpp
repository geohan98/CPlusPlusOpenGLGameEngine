#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "editorCameraController.h"
#include "Headers/cameras/camera3D.h"
#include "Headers/systems/inputPoller.h"
#include "Headers/systems/ButtonCodes.h"
#include "Headers/events/applicationEvents.h"

namespace ParticleEditor
{

	void EditorCameraController::init(float a, float b, float c, float d)
	{
		m_camera = std::shared_ptr<Engine::Camera>(new Engine::Camera3D(a, b, c, d));
		rot = glm::vec2(5, 0);
	}

	void EditorCameraController::onUpdate(float deltaTime)
	{
		if (Engine::Systems::InputPoller::isKeyPressed(KEY_W))
		{
			rot.x += deltaTime * m_turnSpeed;
		}
		if (Engine::Systems::InputPoller::isKeyPressed(KEY_S))
		{
			rot.x += deltaTime * -m_turnSpeed;
		}
		if (Engine::Systems::InputPoller::isKeyPressed(KEY_D))
		{
			rot.y += deltaTime * -m_turnSpeed;
		}
		if (Engine::Systems::InputPoller::isKeyPressed(KEY_A))
		{
			rot.y += deltaTime * m_turnSpeed;
		}

		rot.x = glm::clamp(rot.x, 10.0f, 80.0f);

		glm::vec3 pos;
		glm::quat r = glm::angleAxis(glm::radians(rot.x), glm::vec3(1, 0, 0)) * glm::angleAxis(glm::radians(rot.y), glm::vec3(0, 1, 0)) * glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
		pos = glm::vec3(0, 0, -zoom) * r;


		m_camera->setPosition(pos);
		m_camera->setRotation(glm::vec3(rot.x, rot.y, 0));
		m_camera->update();
	}

	void EditorCameraController::onEvent(Engine::Events::Event& _e)
	{
		Engine::Events::EventDispatcher dispatcher(_e);
		dispatcher.dispatch<Engine::Events::WindowResize>(std::bind(&CameraController::resizeEvent, this, std::placeholders::_1));
	}

	bool EditorCameraController::resizeEvent(Engine::Events::WindowResize& e)
	{
		m_camera->resize(e.getWidth(), e.getHeight());
		return false;
	}

}