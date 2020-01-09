#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	/**
	 *  Camera, Abstract Virtual Class, Handles Projection and View Matrix Calculation
	 */
	class Camera
	{
	protected:
		glm::vec3 m_position; ///< The position of the camera in 3D space
		glm::vec3 m_rotation; ///< The Euler rotation of the camera
		glm::mat4 m_projection; ///< The projection matrix of the camera
		glm::mat4 m_view; ///< The view matrix of the camera
		glm::mat4 m_viewProjection; ///< Projection Matrix * View Maxtrix
	public:
		glm::vec3 getPosition() { return m_position; } ///< Return the position vector
		void setPosition(glm::vec3 position) { m_position = position; } ///< Sets the position vector
		glm::vec3 getRotation() { return m_rotation; } ///< Return the rotation vector
		void setRotation(glm::vec3 rotation) { m_rotation = rotation; } ///< Sets the rotation vector

		const glm::mat4& getProjection() { return m_projection; }  ///< Returns the projection matrix
		const glm::mat4& getView() { return m_view; } ///< Returns the view matrix
		const glm::mat4& getViewProjection() { return m_viewProjection; } ///< Returns Projection Matrix * View Maxtrix

		virtual void update() = 0; ///< Update the camera matrices
	};
}