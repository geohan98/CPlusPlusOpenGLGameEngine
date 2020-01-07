#pragma once
#include <memory>
#include "layers/layer.h"
#include "systems/system.h"

namespace Engine
{
	class LayerStack : public System
	{
	private:
		std::vector <std::shared_ptr<Layer>> m_layers;
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
		void push(std::shared_ptr<Layer> layer);
		void pop();
		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_layers.begin(); };
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_layers.end(); };
	};
}

