#pragma once
#include "Headers/layers/layer.h"
//#include "Headers/audio/audio.h"

namespace Engine {
	class ImGUILayer : public Layer {
	public:
		ImGUILayer();
		~ImGUILayer();

		//Audio audioEngine;

		void onAttach() override; ///< Run on layer stack attach
		void onDetach() override; ///< Run on layer stack removal
		void onUpdate(float deltaTime) override; ///< Run every frame
		void onEvent(Events::Event& e) override; ///< Run on an Event
	};
}