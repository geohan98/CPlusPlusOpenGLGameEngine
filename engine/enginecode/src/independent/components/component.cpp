#include "engine_pch.h"
#include "systems/log.h"
#include "components/component.h"
#include "core/gameObject.h"

namespace Engine
{
	void Component::sendMessage(const ComponentMessage& msg)
	{
		for (std::vector<std::shared_ptr<Component>>::iterator it = m_parent->begin(); it != m_parent->end(); ++it)
		{
			(*it)->receiveMessage(msg);
		}

	}
}