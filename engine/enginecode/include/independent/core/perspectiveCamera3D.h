#pragma once
#include "core/camera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	class PerspectiveCamera3D : public Camera
	{
	private:
		glm::vec3 m_position = glm::vec3(0.0f);
		glm::quat m_orientation;
		void updateView() override;
	public:
		PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip);
		void reset(float fov, float aspectRatio, float nearClip, float farClip);
		inline glm::vec3 getPosition() const { return m_position; }
		void setView(const glm::mat4& view) { m_view = view; m_viewProjection = m_projection * m_view; }
	};
}