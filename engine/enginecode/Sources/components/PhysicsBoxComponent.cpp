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

		void PhysicsBoxComponent::onEvent(Events::Event& e)
		{
		}

		void PhysicsBoxComponent::receiveMessage(const ComponentMessage& msg)
		{
		}

		void PhysicsBoxComponent::enableGravity(bool isenabled)
		{
			m_body->enableGravity(isenabled);
		}

		void PhysicsBoxComponent::addForce(glm::vec3 force, glm::vec3 point)
		{

			rp3d::Vector3 Force = rp3d::Vector3(force.x, force.y, force.z);
			rp3d::Vector3 Point = rp3d::Vector3(point.x, point.y, point.z);
			m_body->applyForce(Force, Point);
		}

		void PhysicsBoxComponent::addTorque(glm::vec3 torque)
		{
			rp3d::Vector3 Torque = rp3d::Vector3(torque.x, torque.y, torque.z);
			m_body->applyTorque(Torque);
		}

		void PhysicsBoxComponent::setAngularVelocity(glm::vec3 angularVelocity)
		{
			rp3d::Vector3 AngularVelocity = rp3d::Vector3(angularVelocity.x, angularVelocity.y, angularVelocity.z);
			m_body->setAngularVelocity(AngularVelocity);
		}

		void PhysicsBoxComponent::setLinearVelocity(glm::vec3 linearVelocity)
		{
			rp3d::Vector3 LinearVelocity = rp3d::Vector3(linearVelocity.x, linearVelocity.y, linearVelocity.z);
			m_body->setLinearVelocity(LinearVelocity);
		}


		PhysicsBoxComponent::PhysicsBoxComponent(glm::vec3 Position, glm::vec4 Orientation, glm::vec3 boxSize, float density, bool useGravity)
		{
			rp3d::Vector3 initialPosition(Position.x, Position.y, Position.z);
			rp3d::Quaternion initialOrientation = rp3d::Quaternion::identity();
			rp3d::Transform initialTransform(initialPosition, initialOrientation);
			//Add Body
			m_body = Systems::Physics::GetInstance()->getWorld()->createRigidBody(initialTransform);
			//Create Box Shape
			rp3d::Vector3 halfExtents(boxSize.x, boxSize.y, boxSize.z);
			m_shape = new rp3d::BoxShape(halfExtents);
			//Add Shape to Rigibody
			m_proxy = m_body->addCollisionShape(m_shape, rp3d::Transform::identity(), 1.0);
			m_body->enableGravity(useGravity);
		}

		void PhysicsBoxComponent::onDetach()
		{
			Systems::Physics::GetInstance()->getWorld()->destroyRigidBody(m_body);
		}
	}
}