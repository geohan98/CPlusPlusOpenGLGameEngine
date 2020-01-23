#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/core/gameObject.h"

namespace Engine
{

	void GameObject::onUpdate(float deltaTime)
	{
		for (auto& it : m_components)
		{
			it->onUpdate(deltaTime);
		}
	}

	void GameObject::onEvent(Events::Event& e)
	{
		for (auto& it : m_components)
		{
			it->onEvent(e);
		}
	}

	void GameObject::addComponent(const std::shared_ptr<Component>& comp)
	{
		m_components.push_back(comp);
		m_components.back()->onAttach(this);
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