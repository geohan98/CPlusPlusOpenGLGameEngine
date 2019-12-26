#pragma once
#include "cameras/camera.h"

namespace Engine
{
	class Camera3D : public Camera
	{
	public:
		Camera3D(float fov, float aspectRatio, float nearClip, float farClip);
		void update() override;
	};
}