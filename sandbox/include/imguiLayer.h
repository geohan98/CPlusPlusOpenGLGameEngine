#pragma once
#include "Headers/layers/layer.h"
#include "Headers/audio/audio.h"

namespace Engine {
	class ImGUILayer : public Layer {
	public:
		ImGUILayer();

		void onAttach() override; ///< Run on layer stack attach
		void onDetach() override; ///< Run on layer stack removal
		void onUpdate(float deltaTime); ///< Run every frame
		void onEvent(Events::Event& e) {}; ///< Run on an Event
	};
}