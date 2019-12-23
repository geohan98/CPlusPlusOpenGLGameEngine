#pragma once
#include "core/camera.h"
#include "events/event.h"
#include <memory>

namespace Engine
{
	class CameraController
	{
	public:
		virtual void init(float a, float b, float c, float d) = 0;
		virtual std::shared_ptr<Camera> getCamera() = 0;
		virtual void onUpdate(float timestep) = 0;
		virtual void onEvent(Event& e) = 0;
		virtual void onResize() = 0;
	};
}