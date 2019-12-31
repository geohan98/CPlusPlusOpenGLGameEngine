#pragma once
#include "cameras/cameraController.h"

namespace Engine
{
	class CameraController2D : public CameraController
	{
	private:
		float m_translateSpeed = 1.0f;
		float m_rotateSpeed = 90.0f;
	public:
		void init(float a, float b, float c, float d) override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
		void onResize() override;
	};
}