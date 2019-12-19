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
		inline glm::quat getOrientation() const { return m_orientation; }
		void setPosition(glm::vec3& position) { m_position = position; updateView(); }
		void setOrientation(glm::quat& orientation) { m_orientation = orientation; updateView(); }
		void setPositionRotation(const glm::vec3& position, glm::quat& orientation) { m_position = position; m_orientation = orientation; updateView(); }
	};
}