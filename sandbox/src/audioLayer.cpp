#include "engine_pch.h"

#include "..\include\audioLayer.h"

namespace Engine{
	AudioLayer::AudioLayer() : Layer("AudioLayer") {};

	void AudioLayer::onAttach()
	{
		audioEngine->Init();
		

		audioEngine->LoadBank("assets/audio/master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		audioEngine->LoadBank("assets/audio/master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);

		audioEngine->LoadSound("assets/audio/woo.mp3", false);
	}

	void AudioLayer::onUpdate(float deltaTime)
	{
		audioEngine->Update();
		
		if (Systems::InputPoller::isKeyPressed(KEY_B)) {
			audioEngine->PlaySounds("assets/audio/woo.mp3", { 0,0,0 }, 1.f);
		}
	}
}