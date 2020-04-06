#pragma once
#include "Headers/cameras/cameraController.h"

namespace Engine
{
	/**
	 * CameraController3D, Creates a 3D Camera
	 */
	class EditorCameraController : public CameraController
	{
	private:
		glm::vec2 rot;
		float zoom = 2.0f;
		float m_turnSpeed = 50.0f;
	public:
		void init(float a, float b, float c, float d) override; ///< Creates a 3D camera
		void onUpdate(float deltaTime) override; ///< Called every Frame, checks for player input and moves camera.
		void onEvent(Events::Event& _e) override; ///< Called on Event
		bool resizeEvent(Events::WindowResize& e) override;
	};
}