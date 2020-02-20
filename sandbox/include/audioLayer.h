#pragma once

#include "../enginecode/Headers/audio/audio.h"
#include "../enginecode/Headers/layers/layer.h"
#include "../enginecode/Headers/events/applicationEvents.h"
#include "../enginecode/Headers/events/keyEvents.h"
#include "../enginecode/Headers/systems/inputPoller.h"
#include "../enginecode/Headers/systems/ButtonCodes.h"

namespace Engine {
	class AudioLayer : public Layer {		
	public:
		std::shared_ptr<Systems::Audio> audioEngine;

		AudioLayer();

		void onAttach(); ///< Run on layer stack attach
		void onDetach() {}; ///< Run on layer stack remove
		void onUpdate(float deltaTime); ///< Run every frame
		void onEvent(Events::Event& e) {}; ///< Run on an Event
	};
}