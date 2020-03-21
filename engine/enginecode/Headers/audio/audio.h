#pragma once

#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <../enginecode/Headers/systems/system.h>

using namespace std;

namespace Engine {
	namespace Systems {
		struct Vector3 {
			float x;
			float y;
			float z;
		};

		struct AudioImplementation {
			AudioImplementation();

			void update();

			FMOD::Studio::System* fmodStudioSystem;
			FMOD::System* fmodSystem;

			int fmodNextChannelId;

			typedef map<string, FMOD::Sound*> fmodSoundMap;
			typedef map<int, FMOD::Channel*> fmodChannelMap;
			typedef map<string, FMOD::Studio::EventInstance*> fmodEventMap;
			typedef map<string, FMOD::Studio::Bank*> fmodBankMap;
			fmodBankMap fmodBanks;
			fmodEventMap fmodEvents;
			fmodSoundMap fmodSounds;
			fmodChannelMap fmodChannels;
		};

		class Audio : public System {
		public:
			static void start(SystemSignal init = SystemSignal::None, ...);
			static void stop(SystemSignal close = SystemSignal::None, ...);

			static void update();
			static int errorCheck(FMOD_RESULT result);

			static int playSound(const string& strSoundName, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
			static void loadSound(const string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
			static void loadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);

			void playEvent(const string& strEventName);
			void loadEvent(const std::string& strEventName);
			void unLoadSound(const string& strSoundName);
			void getEventParameter(const string& strEventName, const string& strEventParameter, float* parameter);
			void setEventParameter(const string& strEventName, const string& strParameterName, float fValue);
			void stopEvent(const string& strEventName, bool bImmediate = false);
			void setChannel3dPosition(int nChannelId, const Vector3& vPosition);
			void setChannelVolume(int nChannelId, float fVolumedB);
			bool isEventPlaying(const string& strEventName) const;
			FMOD_VECTOR static vectorToFmod(const Vector3& vPosition);
			float static dbToVolume(float dB);
			float static volumeTodB(float volume);

			void set3dListenerAndOrientation(const Vector3& vPosition, const Vector3& vLook, const Vector3& vUp);
			void stopChannel(int nChannelId);
			bool isPlaying(int nChannelId) const;
			void stopAllChannels();
		};
	}
#endif
}

#define START_SOUND_ENGINE(...) Systems::Audio::start(__VA_ARGS__);
#define LOAD_SOUND_BANK(...) Systems::Audio::loadBank(__VA_ARGS__)
#define LOAD_SOUND(...) Systems::Audio::loadSound(__VA_ARGS__)
#define PLAY_SOUND(...) Systems::Audio::playSound(__VA_ARGS__)
#define UPDATE_SOUND_ENGINE(...) Systems::Audio::update(__VA_ARGS__);