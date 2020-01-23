#pragma once
#include "../components/component.h"
#include <glm/glm.hpp>

namespace Engine
{
	/**
	 *  Velocity Component, Handles movement
	 */
	class VelocityComponent : public Component
	{
	private:

		glm::vec3 m_linear; ///< Liner Velocity of the game object
		glm::vec3 m_angular; ///< Angular velocity of the game object

	public:

		VelocityComponent(glm::vec3 linear, glm::vec3 angular) : m_linear(linear), m_angular(angular) {} ///< Constructor
		void onUpdate(float deltaTime) override ///< Called every frame, sends velocity data to other components
		{
			std::pair<glm::vec3, glm::vec3> data(m_linear * deltaTime, m_angular * deltaTime);
			sendMessage(ComponentMessage(ComponentMessageType::PositionIntergrate, std::any(data)));
		}

		void receiveMessage(const ComponentMessage& msg) override ///< Receive message from other components, update velocity data
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::VelocitySetLinear:
			{
				glm::vec3 data = std::any_cast<glm::vec3> (msg.m_msgData);
				m_linear = data;
				return;
			}
			case ComponentMessageType::VelocitySetAngular:
			{
				glm::vec3 data = std::any_cast<glm::vec3> (msg.m_msgData);
				m_angular = data;
				return;
			}
			}
		}

	};

}