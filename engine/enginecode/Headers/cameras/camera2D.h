#pragma once
#include "camera.h"

namespace Engine
{
	/**
	 *  Camera2D, Creates an Orthographic Projection Matrix
	 */
	class Camera2D : public Camera
	{
	private:
		float m_left;
		float m_right;
		float m_top;
		float m_bottom;
	public:
		Camera2D(float left, float right, float top, float bottom); ///< Constructor
		void update() override; ///< Updates the View and Projection Matrix for a orthographic View
		void resize(float a, float b) override;
	};
}
