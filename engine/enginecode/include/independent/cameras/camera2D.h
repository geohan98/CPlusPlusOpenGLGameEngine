#pragma once
#include "cameras/camera.h"

namespace Engine
{
	/**
	 *  Camera2D, Creates an Orthographic Projection Matrix
	 */
	class Camera2D : public Camera
	{
	public:
		Camera2D(float left, float right, float top, float bottom); ///< Constructor
		void update() override; ///< Updates the View and Projection Matrix for a orthographic View
	};
}
