#pragma once
#include "core/cameraController.h"
#include "core/perspectiveCamera3D.h"
#include "events/mouseEvents.h"

namespace Engine
{
	class PerspectiveCameraController : public CameraController
	{
	private:
		std::shared_ptr<PerspectiveCamera3D> m_camera;
		glm::mat4 m_view;
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;
		float m_yaw;
		float m_pitch;
		float m_translationSpeed;
		float m_rotationSpeed;
		glm::vec2 m_lastMousePos;
		void updateView();
	public:
		PerspectiveCameraController();
		void init(float a, float b, float c, float d) override;
		std::shared_ptr<Camera> getCamera() override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
		void onResize() override;
		bool onMouseButton(MouseButtonPressed& e);
	};
}