

#include <map>
#include <memory>
#include <string>
#include "systems/log.h"

namespace Engine
{
	template<class G>
	class AssetManager
	{
	private:
		std::map<std::string, std::shared_ptr<G>> m_container;
	public:
		bool contains(const std::string& key);
		void add(const std::string key, std::shared_ptr<G>& element);
		std::shared_ptr<G> get(const std::string& key);
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
		LOG_CORE_ERROR("UNABLE TO FIND '{0}'", key);
		return std::shared_ptr<G>(nullptr);
	}
}