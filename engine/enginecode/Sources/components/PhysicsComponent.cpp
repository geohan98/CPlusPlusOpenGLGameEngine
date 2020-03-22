#include "engine_pch.h"
#include "Headers/components/PhysicsComponent.h"
#include "Headers/systems/Physics.h"
namespace Engine {






	void PhysicsComponent::onUpdate(float deltaTime)
	{

		glm::mat4 model(1.0);
		auto transform = m_body->getTransform();
		transform.getOpenGLMatrix(&model[0][0]);

		ComponentMessage msg(ComponentMessageType::ModelMatrixSet, model);
		sendMessage(msg);

	}

	void PhysicsComponent::onEvent(Events::Event& e)
	{
	}

	void PhysicsComponent::receiveMessage(const ComponentMessage& msg)
	{
	}

	void PhysicsComponent::setup(glm::vec3 Position, glm::vec4 Orientation, glm::vec3 boxSize, float density)
	{

		rp3d::Vector3 initialPosition(Position.x, Position.y, Position.z);
		rp3d::Quaternion initialOrientation = rp3d::Quaternion::identity();
		rp3d::Transform initialTransform(initialPosition, initialOrientation);

		m_body = Systems::Physics::GetInstance()->getWorld()->createRigidBody(initialTransform);

		rp3d::BoxShape shape(rp3d::Vector3(boxSize.x, boxSize.y, boxSize.z));
		rp3d::decimal mass = boxSize.x * boxSize.y * boxSize.z * density;
		m_shape = &shape;
		m_proxy = m_body->addCollisionShape(&shape, rp3d::Transform::identity(), mass);


	}



	PhysicsComponent::PhysicsComponent()
	{
		m_proxy = nullptr;
		m_body = nullptr;
		m_shape = nullptr;
	}

	void PhysicsComponent::onDetach()
	{
		m_body->removeCollisionShape(m_proxy);
		delete m_proxy;
		Systems::Physics::GetInstance()->getWorld()->destroyRigidBody(m_body);
		delete m_body;

		m_parent = nullptr;
	}

}