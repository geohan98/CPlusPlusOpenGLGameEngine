#pragma once
#include "core/camera.h"

namespace Engine
{
	class OrthographicCamera2D : public Camera
	{
	private:
		glm::vec2 m_position = glm::vec2(0.0f);
		float m_rotation = 0.0f;
	public:
		void updateView() override;
		OrthographicCamera2D(float left, float right, float bottom, float top);
		void reset(float left, float right, float bottom, float top);
		inline glm::vec2 getPosition() const { return m_position; }
		inline float getRotation() const { return m_rotation; }
		void setPosition(glm::vec2& position) { m_position = position; updateView(); }
		void setRotation(float& rotation) { m_rotation = rotation; updateView(); }
		void setPositionRotation(const glm::vec2& position, float rotation) { m_position = position; m_rotation = rotation; updateView(); }
	};
}