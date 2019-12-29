#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	class Camera
	{
	protected:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

	public:
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		glm::vec3 getPosition() { return m_position; }
		void setPosition(glm::vec3 position) { m_position = position; }
		glm::vec3 getRotation() { return m_rotation; }
		void setRotation(glm::vec3 rotation) { m_rotation = rotation; }

		const glm::mat4& getProjection() { return m_projection; }
		const glm::mat4& getView() { return m_view; }
		const glm::mat4& getViewProjection() { return m_viewProjection; }

		virtual void update() = 0;
	};
}