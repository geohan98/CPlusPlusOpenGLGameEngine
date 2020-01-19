#pragma once

#include "windows/windowSystem.h"
#include "windows/window.h"

namespace Engine
{
	namespace Systems {
		/**
		 * GL Vertex Buffer
		 */
		class GLFW_WindowSys : public WindowSystem
		{
		public:
			void start(SystemSignal init = SystemSignal::None, ...) override;  ///< Start the window system
			void stop(SystemSignal close = SystemSignal::None, ...) override;  ///< Stop the window system
		};
	}
}