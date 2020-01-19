#pragma once
#include "components/component.h"
#include <memory>
#include <vector>

namespace Engine
{
	/**
	 *  GameObject, handles Components
	 */
	class GameObject
	{
	protected:
		std::string m_name = "GameObject"; ///< Game object Name
		std::vector<std::shared_ptr<Component>> m_components; ///< Vector of Components
	public:
		GameObject() {}; ///< Default Constructor
		GameObject(std::string& name) : m_name(name) {}; ///< Constructor
		void onUpdate(float deltaTime); ///< Called Every Frame
		void onEvent(Events::Event& e); ///< Called on an Event
		void addComponent(const std::shared_ptr<Component>& comp); ///< Add a new Component To the Game object
		void removeComponent(std::vector<std::shared_ptr<Component>>::iterator itt); ///< Removes a Component From the Game object
		void sendMessage(const ComponentMessage& msg)
		{
			for (auto component : m_components)
			{
				component->receiveMessage(msg);
			}
		}

		template<typename G>
		std::vector<std::shared_ptr<Component>>::iterator getComponent() ///< Returns a Component
		{
			auto result = m_components.end();
			for (auto it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(decltype(*(it->get()))).hash_code() == typeid(G).hash_code()) return it;
			}

			return result;
		}

		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); } ///< Component Begin Iterator
		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); } ///< Component End Iterator
	};
}