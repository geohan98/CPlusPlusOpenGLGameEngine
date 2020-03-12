#include "engine_pch.h"
#include "Headers/systems/Physics.h"
#include "btBulletDynamicsCommon.h"

namespace Engine {
	namespace Systems {

		btDiscreteDynamicsWorld* Physics::s_world = nullptr;

		Physics::Physics()
		{
		}
		void Physics::onUpdate(float deltaTime)
		{
			s_world->stepSimulation(deltaTime,10);

			for (int i = s_world->getNumCollisionObjects() - 1; i >= 0; i--)
			{
				btCollisionObject* obj = s_world->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				btTransform trans;
				if (body && body->getMotionState())
				{
					body->getMotionState()->getWorldTransform(trans);
				}
				else
				{
					trans = obj->getWorldTransform();
				}
			}

		}
		void Physics::start(SystemSignal init, ...)
		{
			m_collisionConfiguration = new btDefaultCollisionConfiguration();
			m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
			m_overlappingPairCache = new btDbvtBroadphase();
			m_solver = new btSequentialImpulseConstraintSolver;
			s_world = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);
			s_world->setGravity(btVector3(0, -10, 0));
		}

		void Engine::Systems::Physics::stop(SystemSignal close, ...)
		{
		}
	}
}
