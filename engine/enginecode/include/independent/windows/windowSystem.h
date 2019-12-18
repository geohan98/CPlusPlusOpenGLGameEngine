
#include "systems/system.h"

namespace Engine
{
	class WindowSystem : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0;
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0;
	};
}