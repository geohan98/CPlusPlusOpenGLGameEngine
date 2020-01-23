#pragma once
#include "camera.h"

namespace Engine
{
	/**
	 *  Camera3D, Creates an Perspective Projection Matrix
	 */
	class Camera3D : public Camera
	{
	public:
		Camera3D(float fov, float aspectRatio, float nearClip, float farClip); ///< Constructor
		void update() override; ///< Updates the View and Projection Matrix for a perspective View
	};
}