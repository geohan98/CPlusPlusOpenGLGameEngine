#pragma once
#include "reactphysics3d.h"
#include "Headers/systems/system.h"
#include "Headers/components/physicsComponent.h"
#include "Headers/systems/log.h"

namespace Engine {

	class CollisionListener : public reactphysics3d::EventListener
	{
	public:
		void newContact(const reactphysics3d::CollisionCallback::CollisionCallbackInfo& _collisionInfo) override
		{
			if (_collisionInfo.body1->getUserData() == nullptr || _collisionInfo.body2->getUserData() == nullptr)
			{
				LOG_CORE_ERROR("[PHYSICS][COLLISION LISTENER][MISSING USER DATA]");
				return;
			}
			Engine::Components::PhysicsComponent* body1 = (Engine::Components::PhysicsComponent*)_collisionInfo.body1->getUserData();
			Engine::Components::PhysicsComponent* body2 = (Engine::Components::PhysicsComponent*)_collisionInfo.body2->getUserData();
			body1->onCollision(*body2);
			body2->onCollision(*body1);
			LOG_CORE_ERROR("[PHYSICS][COLLISION LISTENER][COLLISION DETECTED WITH USER DATA]");
		}
	};



	namespace Systems {

		class Physics : public System
		{
		private:
			std::shared_ptr<rp3d::DynamicsWorld> m_world;
			static std::shared_ptr<Physics> s_instance;
			CollisionListener m_listener;
		public:
			Physics();
			static std::shared_ptr<Physics> GetInstance();

			std::shared_ptr<rp3d::DynamicsWorld> getWorld();
			void start(SystemSignal init = SystemSignal::None, ...); //!< Start the system
			void stop(SystemSignal close = SystemSignal::None, ...); //!< Stop the system

		};

	}



}