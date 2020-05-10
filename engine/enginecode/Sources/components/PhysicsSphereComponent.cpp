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

	PhysicsSphereComponent::PhysicsSphereComponent(glm::vec3 Position, glm::vec4 Orientation, float radius, float density)
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
	}

	void PhysicsSphereComponent::onDetach()
	{
		Systems::Physics::GetInstance()->getWorld()->destroyRigidBody(m_body);
	}

}