#pragma once
#include "../components/component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Engine
{
	namespace Components {
		/**
		 *  Position Component, Handles Positioning and Matrix Calculation
		 */
		class PositionComponent : public Component
		{
		private:

			glm::mat4 m_model; ///< Model Matrix
			glm::mat4 m_translation; ///<Translation Matrix
			glm::mat4 m_rotation; ///< Rotation Matrix
			glm::mat4 m_scale; ///< Scale Matrix
			glm::vec3 m_transVec; ///< Position Vector
			glm::vec3 m_rotVec; ///< Rotation Vector
			glm::vec3 m_scaleVec; ///< Scale Vector

			inline void caclulateModel() ///< Calculate All Matrices
			{
				m_translation = glm::translate(glm::mat4(1.0f), m_transVec);
				m_rotation = glm::toMat4(glm::quat(m_rotVec));
				m_scale = glm::scale(m_scaleVec);
				m_model = m_translation * m_rotation * m_scale;
			}

		public:

			PositionComponent(glm::vec3 trans, glm::vec3 rot, glm::vec3 scale) : m_transVec(trans), m_rotVec(rot), m_scaleVec(scale), m_model(glm::mat4(1.0f)) ///< Constructor
			{
				m_rotVec.x = glm::radians(m_rotVec.x);
				m_rotVec.y = glm::radians(m_rotVec.y);
				m_rotVec.z = glm::radians(m_rotVec.z);
				caclulateModel();
			}

			inline std::shared_ptr<glm::mat4> getTransform() { return std::make_shared<glm::mat4>(m_model); } ///< Return the model matrix

			void onAttach(GameObject* parent) override ///< Called when Added to Parent
			{

				m_parent = parent;
				std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
				ComponentMessage msg(ComponentMessageType::UniformSet, data);
				sendMessage(msg);
			}

			void onUpdate(float deltaTime) override ///< Called Every Frame, Sends model matrix to other Components
			{
				caclulateModel();
				std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
				ComponentMessage msg(ComponentMessageType::UniformSet, data);
				sendMessage(msg);
			}

			void receiveMessage(const ComponentMessage& msg) override ///< Receive a message from other components
			{
				switch (msg.m_msgType)
				{
				case ComponentMessageType::ModelMatrixSet:
				{
					glm::mat4 mod = std::any_cast<glm::mat4>(msg.m_msgData);

					glm::vec3 scale;
					glm::quat rotation;
					glm::vec3 skew;
					glm::vec4 perspective;
					glm::decompose(mod, scale, rotation, m_transVec, skew, perspective);

					m_rotVec = glm::eulerAngles(rotation);

					return;
				}
				case ComponentMessageType::PositionSet:
				{
					glm::vec3 pos = std::any_cast<glm::vec3>(msg.m_msgData);
					m_transVec = pos;
					return;
				}
				case ComponentMessageType::PositionIntergrate:
				{
					std::pair<glm::vec3, glm::vec3> vel = std::any_cast<std::pair<glm::vec3, glm::vec3>>(msg.m_msgData);
					m_transVec += vel.first;
					m_rotVec.x += glm::radians(vel.second.x);
					m_rotVec.y += glm::radians(vel.second.y);
					m_rotVec.z += glm::radians(vel.second.z);
					return;
				}
				}
			}

		};

	}
}