#pragma once
#include "engine_pch.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "Headers/components/component.h"
#include "glm/glm.hpp"
#include "Headers/systems/Physics.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace Engine {

	class PhysicsComponent : public Component {

	public:
		PhysicsComponent() {}
		PhysicsComponent(glm::vec3 boxSize, glm::vec3 transform)
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

				std::shared_ptr< btDefaultMotionState> motionState = std::shared_ptr<btDefaultMotionState>(new btDefaultMotionState(Transform));
				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, &(*motionState), &(*m_collisionShape), localInertia);

				btRigidBody* body = new btRigidBody(rbInfo);

				Systems::Physics::getWorld()->addRigidBody(body);
			}


		}
		void onUpdate(float deltaTime) override ///< Called Every Frame
		{
			btQuaternion quat = m_collision->getWorldTransform().getRotation();
			btVector3 pos = m_collision->getWorldTransform().getOrigin();
			btVector3 scale = m_collision->getCollisionShape()->getLocalScaling();

			glm::mat4 mat = glm::mat4(glm::toMat4(glm::quat(quat.getW(), quat.getX(), quat.getY(), quat.getZ()))  * glm::translate(glm::mat4(1.0f), glm::vec3(pos.x(), pos.y(), pos.z()))   * glm::scale(glm::vec3(scale.x(), scale.y(), scale.z())));

			sendMessage(ComponentMessage(ComponentMessageType::PositionSet, mat));

		}

		void receiveMessage(const ComponentMessage& msg) override ///< Receive a message from another component
		{
		}
	private:
		std::shared_ptr<btCollisionObject> m_collision;
		std::shared_ptr<btCollisionShape> m_collisionShape;
		std::shared_ptr<btTransform> m_transform;


	};
}