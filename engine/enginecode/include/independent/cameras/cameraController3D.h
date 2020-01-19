#pragma once
#include "cameraController.h"

namespace Engine
{
	/**
	 * CameraController3D, Creates a 3D Camera
	 */
	class CameraController3D : public CameraController
	{
	private:
		float m_translateSpeed = 1.0f; ///< Move Speed of the Camera
		float m_rotateSpeed = 90.0f; ///< Rotation Speed of the Camera
	public:
		void init(float a, float b, float c, float d) override; ///< Creates a 3D camera
		void onUpdate(float deltaTime) override; ///< Called every Frame, checks for player input and moves camera.
		void onEvent(Events::Event& e) override {}; ///< Called on Event
	};
}