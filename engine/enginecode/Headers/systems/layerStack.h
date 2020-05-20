#pragma once
#include <memory>
#include "../enginecode/Headers/layers/layer.h"
#include "../enginecode/Headers/systems/system.h"

namespace Engine
{
	namespace Systems {
		/**
		 * Layer Stack, Allow ordering of game layers
		 */
		class LayerStack : public System
		{
		private:
			std::vector <std::shared_ptr<Layer>> m_layers;											///< Vector of layers
		public:
			void start(SystemSignal init = SystemSignal::None, ...) override;						///< start the layer stack
			void stop(SystemSignal close = SystemSignal::None, ...) override;						///< stop the layer stack
			std::shared_ptr<Engine::Layer> push(std::shared_ptr<Layer> layer);												///< add a layer to the stack
			void pop();																				///< remove the last layer in the stack
			std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_layers.begin(); };		///< layer stack begin iterator
			std::vector<std::shared_ptr<Layer>>::iterator end() { return m_layers.end(); };			///< layer stack end iterator
		};
	}
}

