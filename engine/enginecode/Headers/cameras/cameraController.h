#pragma once
#include "camera.h"
#include <memory>

namespace Engine
{
	namespace Events
	{
		class Event;
		class WindowResize;
	}

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
		virtual bool resizeEvent(Events::WindowResize& e) = 0;
		virtual void setPosition(glm::vec3 _pos) { m_camera->setPosition(_pos); }
		virtual void setRotation(glm::vec3 _rot) { m_camera->setRotation(_rot); }
	};
}