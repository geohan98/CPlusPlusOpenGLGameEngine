#pragma once

#include <map>
#include <memory>
#include <string>
#include "systems/log.h"

namespace Engine
{
	/**
	 * Asset Manager, template class for handling a single type
	 */
	template<class G>
	class AssetManager
	{
	private:
		std::map<std::string, std::shared_ptr<G>> m_container; ///< string and template data type map
	public:
		bool contains(const std::string& key); ///< is an item in the asset manager
		void add(const std::string key, std::shared_ptr<G>& element); ///< add an item to the asset manager
		std::shared_ptr<G> get(const std::string& key); ///< return an element by name
	};

	template<class G>
	inline bool AssetManager<G>::contains(const std::string& key)
	{
		return m_container.find(key) != m_container.end();
	}

	template<class G>
	inline void AssetManager<G>::add(const std::string key, std::shared_ptr<G>& element)
	{
		m_container[key] = element;
	}

	template<class G>
	inline std::shared_ptr<G> AssetManager<G>::get(const std::string& key)
	{
		if (m_container[key])
		{
			return m_container[key];
		}
#ifdef NG_DEBUG
		LOG_CORE_ERROR("UNABLE TO FIND '{0}'", key);
#endif // NG_DEBUG
		return std::shared_ptr<G>(nullptr);
	}
}