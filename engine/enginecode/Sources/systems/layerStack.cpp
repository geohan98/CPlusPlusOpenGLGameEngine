#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/systems/layerStack.h"

namespace Engine
{
	namespace Systems {
		void LayerStack::start(SystemSignal init /*= SystemSignal::None*/, ...)
		{
			m_layers.clear();
		}

		void LayerStack::stop(SystemSignal close /*= SystemSignal::None*/, ...)
		{
			m_layers.clear();
		}

		void LayerStack::push(std::shared_ptr<Layer> layer)
		{
			layer->onAttach();
			m_layers.push_back(layer);
		}

		void LayerStack::pop()
		{
			m_layers.pop_back();
		}

	}
}