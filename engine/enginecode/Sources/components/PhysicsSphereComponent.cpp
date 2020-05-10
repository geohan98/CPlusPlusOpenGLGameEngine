#include "engine_pch.h"
#include "Headers/components/PhysicsSphereComponent.h"
#include "Headers/systems/Physics.h"
namespace Engine {






	void PhysicsSphereComponent::onUpdate(float deltaTime)
	{

		glm::mat4 model(1.0);
		auto transform = m_body->getTransform();
		transform.getOpenGLMatrix(&model[0][0]);

		ComponentMessage msg(ComponentMessageType::ModelMatrixSet, model);
		sendMessage(msg);

	}

	void PhysicsSphereComponent::onEvent(Events::Event& e)
	{
	}

	void PhysicsSphereComponent::receiveMessage(const ComponentMessage& msg)
	{
	}

	void PhysicsSphereComponent::enableGravity(bool isenabled)
	{
		m_body->enableGravity(isenabled);
	}

	void PhysicsSphereComponent::addForce(glm::vec3 force, glm::vec3 point)
	{
		rp3d::Vector3 Force = rp3d::Vector3(force.x, force.y, force.z);
		rp3d::Vector3 Point = rp3d::Vector3(point.x, point.y, point.z);
		m_body->applyForce(Force, Point);
	}

	void PhysicsSphereComponent::addTorque(glm::vec3 torque)
	{
		rp3d::Vector3 Torque = rp3d::Vector3(torque.x, torque.y, torque.z);
		m_body->applyTorque(Torque);
	}

	void PhysicsSphereComponent::setAngularVelocity(glm::vec3 angularVelocity)
	{
		rp3d::Vector3 AngularVelocity = rp3d::Vector3(angularVelocity.x, angularVelocity.y, angularVelocity.z);
		m_body->setAngularVelocity(AngularVelocity);
	}

	void PhysicsSphereComponent::setLinearVelocity(glm::vec3 linearVelocity)
	{
		rp3d::Vector3 LinearVelocity = rp3d::Vector3(linearVelocity.x, linearVelocity.y, linearVelocity.z);
		m_body->setLinearVelocity(LinearVelocity);
	}

	PhysicsSphereComponent::PhysicsSphereComponent(glm::vec3 Position, glm::vec4 Orientation, float radius, float density, bool useGravity = true)
	{
		rp3d::Vector3 initialPosition(Position.x, Position.y, Position.z);
		rp3d::Quaternion initialOrientation = rp3d::Quaternion::identity();
		rp3d::Transform initialTransform(initialPosition, initialOrientation);
		//Add Body
		m_body = Systems::Physics::GetInstance()->getWorld()->createRigidBody(initialTransform);
		//Create Box Shape
		m_shape = new rp3d::SphereShape(radius);
		//Add Shape to Rigibody
		m_proxy = m_body->addCollisionShape(m_shape, rp3d::Transform::identity(), 1.0);
		m_body->enableGravity(useGravity);
	}

	void PhysicsSphereComponent::onDetach()
	{
		Systems::Physics::GetInstance()->getWorld()->destroyRigidBody(m_body);
	}

}