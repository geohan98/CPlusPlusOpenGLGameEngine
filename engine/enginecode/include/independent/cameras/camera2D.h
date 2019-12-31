#pragma once
#include "cameras/camera.h"

namespace Engine
{
	class Camera2D : public Camera
	{
	public:
		Camera2D(float left, float right, float top, float bottom);
		void update() override;
	};
}
