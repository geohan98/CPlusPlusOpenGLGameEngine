#include "engine_pch.h"
#include "systems/log.h"
#include "core/gameObject.h"

namespace Engine
{

	void GameObject::onUpdate(float timestep)
	{
		auto it = m_components.begin();

		for (it; it != m_components.end(); ++it)
		{
			(*it)->onUpdate(timestep);
		}
	}

	void GameObject::onEvent(Event& e)
	{
		auto it = m_components.begin();

		for (it; it != m_components.end(); ++it)
		{
			(*it)->onEvent(e);
		}
	}

	void GameObject::addComponent(const std::shared_ptr<Component>& comp)
	{
		m_components.push_back(comp);
	}

	void GameObject::removeComponent(std::vector<std::shared_ptr<Component>>::iterator itt)
	{
		auto it = m_components.begin();

		for (it; it != m_components.end(); ++it)
		{
			if (it == itt)
			{
				m_components.erase(itt);
			}
		}
	}

}