#pragma once
#include "systems/system.h"

namespace Engine
{
	namespace Systems {

		/**
		 * Resource Manger, Handles resources for the engine
		 */
		class WindowSystem : public System
		{
		public:
			virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; ///<  Start the window System
			virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; ///<  Stop the windiw system
		};
	}
}