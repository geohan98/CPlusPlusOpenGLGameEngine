#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/components/component.h"
#include "../enginecode/Headers/core/gameObject.h"

namespace Engine
{
	namespace Components {
		void Component::sendMessage(const ComponentMessage& msg)
		{
			for (std::vector<std::shared_ptr<Component>>::iterator it = m_parent->begin(); it != m_parent->end(); ++it)
			{
				(*it)->receiveMessage(msg);
			}
		}
	}
}