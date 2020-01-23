#pragma once
#include "camera.h"
#include "../events/event.h"
#include <memory>

namespace Engine
{
	/**
	 *  Camera3D, Handles events and updates for the Camera
	 */
	class CameraController
	{
	protected:
		std::shared_ptr<Camera> m_camera; ///< Smart Pointer to Camera Class
	public:
		virtual void init(float a, float b, float c, float d) = 0; ///< Create the Camera and assigns it to the pointer
		virtual std::shared_ptr<Camera> getCamera() { return m_camera; } ///< Returns the camera pointer
		virtual void onUpdate(float deltaTime) = 0; ///< Called Every Frame
		virtual void onEvent(Events::Event& e) = 0; ///< Called On an Event
	};
}