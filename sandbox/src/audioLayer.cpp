#include "engine_pch.h"

#include "..\include\audioLayer.h"

namespace Engine{
	AudioLayer::AudioLayer() : Layer("AudioLayer") {};

	void AudioLayer::onAttach()
	{		
		START_SOUND_ENGINE();
		LOAD_SOUND_BANK("assets/audio/master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		LOAD_SOUND_BANK("assets/audio/master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		LOAD_SOUND("assets/audio/woo.mp3", false);
	}

	void AudioLayer::onUpdate(float deltaTime)
	{
		UPDATE_SOUND_ENGINE();
		
		if (Systems::InputPoller::isKeyPressed(KEY_B)) {
			PLAY_SOUND("assets/audio/woo.mp3", { 0,0,0 }, 1.f);
		}
	}
}