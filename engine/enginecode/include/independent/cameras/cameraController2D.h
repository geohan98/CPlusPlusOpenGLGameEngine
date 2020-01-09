#pragma once
#include "cameras/cameraController.h"

namespace Engine
{
	/**
	 * CameraController2D, Creates a 2D camera
	 */
	class CameraController2D : public CameraController
	{
	private:
		float m_translateSpeed = 1.0f; ///< Move Speed of the Camera
		float m_rotateSpeed = 90.0f; ///< Rotation Speed of the Camera
	public:
		void init(float a, float b, float c, float d) override; ///< Creates a 2D Camera
		void onUpdate(float deltaTime) override; ///< Called Every Frame
		void onEvent(Event& e) override {}; ///< Called on Event
	};
}