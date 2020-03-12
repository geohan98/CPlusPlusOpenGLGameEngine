#include "engine_pch.h"
#include "Headers/components/PhysicsComponent.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace Engine
{
	PhysicsComponent::PhysicsComponent(glm::vec3 boxSize, glm::vec3 transform)
	{
		// https://github.com/bulletphysics/bullet3/blob/master/examples/HelloWorld/HelloWorld.cpp
		m_collisionShape = std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(boxSize.x, boxSize.y, boxSize.z)));
		btTransform Transform;
		Transform.setIdentity();
		
		btScalar mass(1.f);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
		{
			m_collisionShape->calculateLocalInertia(mass, localInertia);
			
			Transform.setOrigin(btVector3(transform.x, transform.y, transform.z));

			std::shared_ptr< btDefaultMotionState> motionState = std::shared_ptr<btDefaultMotionState>(new btDefaultMotionState( Transform));
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, &(*motionState), &(*m_collisionShape), localInertia);

			btRigidBody* body = new btRigidBody(rbInfo);

			Systems::Physics::getWorld()->addRigidBody(body);
		}


	}

	void PhysicsComponent::onUpdate(float deltaTime)
	{
		btQuaternion quat = m_collision->getWorldTransform().getRotation();
		btVector3 pos = m_collision->getWorldTransform().getOrigin();
		btVector3 scale = m_collision->getCollisionShape()->getLocalScaling();
		
		glm::mat4 mat = glm::mat4(glm::toMat4(glm::quat(quat.getW(), quat.getX(), quat.getY(), quat.getZ()))  * glm::translate(glm::mat4(1.0f),glm::vec3(pos.x(),pos.y(),pos.z()))   * glm::scale(glm::vec3(scale.x(),scale.y(),scale.z())));

		sendMessage(ComponentMessage(ComponentMessageType::PositionSet,mat));
	
	}

	void PhysicsComponent::receiveMessage(const ComponentMessage & msg)
	{
	}

}