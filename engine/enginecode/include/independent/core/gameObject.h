#pragma once
#include "components/component.h"
#include <memory>
#include <vector>

namespace Engine
{
	class GameObject
	{
	protected:
		std::string m_name = "GameObject";
		std::vector<std::shared_ptr<Component>> m_components;
	public:
		GameObject();
		GameObject(std::string& name) : m_name(name) {};
		void onUpdate(float deltaTime);
		void onEvent(Event& e);
		void addComponent(const std::shared_ptr<Component>& comp);
		void removeComponent(std::vector<std::shared_ptr<Component>>::iterator itt);

		template<typename G>
		std::vector<std::shared_ptr<Component>>::iterator getComponent()
		{
			auto result = m_components.end();
			for (auto it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(decltype(*(it->get()))).hash_code() == typeid(G).hash_code()) return it;
			}

			return result;
		}

		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
	};
}