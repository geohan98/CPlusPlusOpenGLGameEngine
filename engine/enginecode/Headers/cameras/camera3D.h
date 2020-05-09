#pragma once
#include "camera.h"

namespace Engine
{
	/**
	 *  Camera3D, Creates an Perspective Projection Matrix
	 */
	class Camera3D : public Camera
	{
	private:
		float m_fov;
		float m_aspectRatio;
		float m_nearClip;
		float m_farClip;
	public:
		Camera3D(float fov, float aspectRatio, float nearClip, float farClip); ///< Constructor
		void update() override; ///< Updates the View and Projection Matrix for a perspective View
		void resize(float a, float b) override; ///< Resize the window, and recalculate the projection matrix
	};
}