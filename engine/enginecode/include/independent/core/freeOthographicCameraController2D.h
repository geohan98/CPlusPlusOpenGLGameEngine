#pragma once
#include "core/cameraController.h"
#include "core/orthographicCamera2D.h"

namespace Engine
{
	class FreeOthographicCameraController2D : public CameraController
	{
	private:
		std::shared_ptr<OrthographicCamera2D> m_camera;
		glm::vec2 m_position = glm::vec2(0.0f);
		float m_rotation = 0.0f;
		float m_translateionSpeed = 100.0f;
		float m_rotationSpeed = 10.0f;
	public:
		FreeOthographicCameraController2D();
		void init(float left, float right, float bottom, float top) override;
		std::shared_ptr<Camera> getCamera() override { return m_camera; }
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override {};
		void onResize() override {};
	};
}