#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/systems/layerStack.h"

namespace Engine
{
	namespace Systems {
		void LayerStack::start(SystemSignal init /*= SystemSignal::None*/, ...)
		{
			m_layers.clear();
			LOG_CORE_WARN("[SYSTEMS][LAYER STACK][LAYER STACK STARTED]");
		}

		void LayerStack::stop(SystemSignal close /*= SystemSignal::None*/, ...)
		{
			m_layers.clear();
			LOG_CORE_WARN("[SYSTEMS][LAYER STACK][LAYER STACK STOPPED]");
		}

		void LayerStack::push(std::shared_ptr<Layer> layer)
		{
			layer->onAttach();
			m_layers.push_back(layer);
			LOG_CORE_INFO("[SYSTEMS][LAYER STACK][ATACHED LAYER:'{0}']", layer->getName());
		}

		void LayerStack::pop()
		{
			m_layers.pop_back();
		}

	}
}