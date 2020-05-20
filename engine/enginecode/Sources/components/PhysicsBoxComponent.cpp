#include "engine_pch.h"
#include "Headers/components/PhysicsBoxComponent.h"
#include "Headers/systems/Physics.h"
namespace Engine {

	namespace Components {
		void PhysicsBoxComponent::onUpdate(float deltaTime)
		{
			glm::mat4 model(1.0);
			auto transform = m_body->getTransform();
			transform.getOpenGLMatrix(&model[0][0]);

			ComponentMessage msg(ComponentMessageType::ModelMatrixSet, model);
			sendMessage(msg);
		}

		PhysicsBoxComponent::PhysicsBoxComponent(glm::vec3 Position, glm::vec4 Orientation, glm::vec3 boxSize, float density, bool useGravity, reactphysics3d::BodyType type)
		{
			rp3d::Vector3 initialPosition(Position.x, Position.y, Position.z);
			rp3d::Quaternion initialOrientation = rp3d::Quaternion::identity();
			rp3d::Transform initialTransform(initialPosition, initialOrientation);
			//Add Body
			m_body = Systems::Physics::GetInstance()->getWorld()->createRigidBody(initialTransform);
			m_body->setIsSleeping(false);
			m_body->setType(type);
			m_body->enableGravity(useGravity);
			m_body->setUserData(this);
			//Create Box Shape
			rp3d::Vector3 halfExtents(boxSize.x / 2.0f, boxSize.y / 2.0f, boxSize.z / 2.0f);
			m_shape = new rp3d::BoxShape(halfExtents);
			//Add Shape to Rigibody
			m_proxy = m_body->addCollisionShape(m_shape, rp3d::Transform::identity(), 1.0);
		}

		void PhysicsBoxComponent::onDetach()
		{
			Systems::Physics::GetInstance()->getWorld()->destroyRigidBody(m_body);
		}
	}
}