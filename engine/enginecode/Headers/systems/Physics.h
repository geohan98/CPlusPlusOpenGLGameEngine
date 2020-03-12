#pragma once
#include "Headers/systems/system.h"

class btDiscreteDynamicsWorld;
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;

namespace Engine {
	namespace Systems {
		class Physics : public System
		{
		private:
			static btDiscreteDynamicsWorld* s_world;
			btCollisionDispatcher* m_dispatcher;
			btDefaultCollisionConfiguration* m_collisionConfiguration;
			btBroadphaseInterface* m_overlappingPairCache;
			btSequentialImpulseConstraintSolver* m_solver;


		public:
			Physics();
			void onUpdate(float deltaTime);
			inline static btDiscreteDynamicsWorld* getWorld() { return s_world; }
			void start(SystemSignal init = SystemSignal::None, ...); //!< Start the system
			void stop(SystemSignal close = SystemSignal::None, ...); //!< Stop the system

		};
	}
}


