#include "engine_pch.h"
#include "Headers/systems/Physics.h"

namespace Engine
{
	namespace Systems
	{
		std::shared_ptr<Physics> Physics::s_instance = nullptr;

		Physics::Physics()
		{
			m_world = nullptr;
		}

		std::shared_ptr<Physics> Physics::GetInstance()
		{
			if (s_instance == nullptr)
			{
				s_instance = std::shared_ptr<Physics>(new Physics);
			}
			return s_instance;
		}

		std::shared_ptr<rp3d::DynamicsWorld> Physics::getWorld()
		{
			return m_world;
		}

		void Physics::start(SystemSignal init, ...)
		{
			rp3d::Vector3 gravity = rp3d::Vector3(0.f, -9.81, 0.f);
			m_world.reset(new rp3d::DynamicsWorld(gravity));
			m_world->setEventListener(&m_listener);
		}

		void Physics::stop(SystemSignal close, ...)
		{

			m_world = nullptr;
		}

	}

}