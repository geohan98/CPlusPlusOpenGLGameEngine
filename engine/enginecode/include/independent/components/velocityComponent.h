#pragma once
#include "components/component.h"
#include <glm/glm.hpp>

namespace Engine
{

	class VelocityComponent : public Component
	{
	private:

		glm::vec3 m_linear;
		glm::vec3 m_angular;

	public:

		VelocityComponent(glm::vec3 linear, glm::vec3 angular) : m_linear(linear), m_angular(angular) {}
		void onUpdate(float timestep) override
		{
			std::pair<glm::vec3, glm::vec3> data(m_linear * timestep, m_angular * timestep);
			LOG_CORE_WARN("VEL COMP {0}", m_angular.y * timestep);
			sendMessage(ComponentMessage(ComponentMessageType::PositionIntergrate, std::any(data)));
		}

		void receiveMessage(const ComponentMessage& msg) override
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