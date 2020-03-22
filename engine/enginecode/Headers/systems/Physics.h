#pragma once
#include "reactphysics3d.h"
#include "Headers/systems/system.h"




namespace Engine {
	namespace Systems {

		class Physics : public System
		{
		private:
			std::shared_ptr<rp3d::DynamicsWorld> m_world;
			static std::shared_ptr<Physics> s_instance;
		public:
			Physics();
			static std::shared_ptr<Physics> GetInstance();

			std::shared_ptr<rp3d::DynamicsWorld> getWorld();
			void start(SystemSignal init = SystemSignal::None, ...); //!< Start the system
			void stop(SystemSignal close = SystemSignal::None, ...); //!< Stop the system



		};

	}
}