#pragma once

#include "windows/windowSystem.h"
#include "windows/window.h"

namespace Engine
{
	class GLFW_WindowSys : public WindowSystem
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
	};
}