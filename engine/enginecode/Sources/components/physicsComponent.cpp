#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "Headers/components/physicsComponent.h"
#include "Headers/systems/Physics.h"

namespace Engine
{
	namespace Components
	{
		void PhysicsComponent::onAttach(GameObject* _parent)
		{
			m_parent = _parent;
		}
		void PhysicsComponent::onDetach()
		{
			m_parent = nullptr;
		}
		void PhysicsComponent::enableGravity(bool _isEnabled)
		{
			if (m_body) m_body->enableGravity(_isEnabled);
		}
		void PhysicsComponent::addForce(glm::vec3 _force, glm::vec3 _point)
		{
			if (m_body)
			{
				rp3d::Vector3 force = rp3d::Vector3(_force.x, _force.y, _force.z);
				rp3d::Vector3 point = rp3d::Vector3(_point.x, _point.y, _point.z);
				m_body->applyForce(force, point);
			}
		}
		void PhysicsComponent::addTorque(glm::vec3 _torque)
		{
			if (m_body)
			{
				rp3d::Vector3 torque = rp3d::Vector3(_torque.x, _torque.y, _torque.z);
				m_body->applyTorque(torque);
			}
		}
		void PhysicsComponent::setAngularVelocity(glm::vec3 _angularVelocity)
		{
			if (m_body)
			{
				rp3d::Vector3 angularVelocity = rp3d::Vector3(_angularVelocity.x, _angularVelocity.y, _angularVelocity.z);
				m_body->setAngularVelocity(angularVelocity);
			}
		}
		void PhysicsComponent::setLinearVelocity(glm::vec3 _linearVelocity)
		{
			if (m_body)
			{
				rp3d::Vector3 linearVelocity = rp3d::Vector3(_linearVelocity.x, _linearVelocity.y, _linearVelocity.z);
				m_body->setLinearVelocity(linearVelocity);
			}
		}
	}
}