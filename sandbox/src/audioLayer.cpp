#include "engine_pch.h"

#include "..\include\audioLayer.h"

namespace Engine{
	AudioLayer::AudioLayer() : Layer("AudioLayer") {};

	void AudioLayer::onAttach()
	{
		//audioEngine->Init();
		//audioEngine->start();
		audioEngine->start();
		//START_SOUND_ENGINE();
		
		audioEngine->LoadBank("assets/audio/master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		audioEngine->LoadBank("assets/audio/master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		//LOAD_SOUND_BANK("assets/audio/master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		//LOAD_SOUND_BANK("assets/audio/master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);

		//LOAD_SOUND("assets/audio/woo.mp3", false);
		audioEngine->LoadSound("assets/audio/woo.mp3", false);
	}

	void AudioLayer::onUpdate(float deltaTime)
	{
		//UPDATE_SOUND_ENGINE();
		audioEngine->Update();
		
		if (Systems::InputPoller::isKeyPressed(KEY_B)) {
			audioEngine->PlaySounds("assets/audio/woo.mp3", { 0,0,0 }, 1.f);
			//PLAY_SOUND("assets/audio/woo.mp3", { 0,0,0 }, 1.f);
		}
	}
}