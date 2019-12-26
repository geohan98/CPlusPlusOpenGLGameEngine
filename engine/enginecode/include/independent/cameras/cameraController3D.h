#pragma once
#include "cameraController.h"

namespace Engine
{
	class CameraController3D : public CameraController
	{
	private:
		float m_moveSpeed = 1.0f;
	public:
		void init(float a, float b, float c, float d) override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
		void onResize() override;
	};
}