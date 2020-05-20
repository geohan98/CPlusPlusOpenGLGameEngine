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
		struct Vector3 { ///< Struct for holding position vectors
			float x;
			float y;
			float z;
		};

		struct AudioImplementation { ///< Used to handle the entire Audio system and is created on start up
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

		/**
		*  Audio System, Manages Audio
		*/
		class Audio : public System {
		public:
			static void start(SystemSignal init = SystemSignal::None, ...); ///< Allows the starting of the Audio system
			static void stop(SystemSignal close = SystemSignal::None, ...); ///< Allows the stopping of the Audio system

			static void update(); ///< Handles the continuous updating of the Audio system
			static int errorCheck(FMOD_RESULT result); ///<

			static int playSound(const string& strSoundName, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f); ///< Play a sound
			static void loadSound(const string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false); ///< Load a sound
			static void loadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags); ///< Load a sound bank

			void playEvent(const string& strEventName); ///< Play an event
			void loadEvent(const std::string& strEventName); ///< Load an event
			void unLoadSound(const string& strSoundName); ///< Unload a ssound
			void getEventParameter(const string& strEventName, const string& strEventParameter, float* parameter); ///< Using an event name get check for an event parameter
			void setEventParameter(const string& strEventName, const string& strParameterName, float fValue); ///< Set an event parameter
			void stopEvent(const string& strEventName, bool bImmediate = false); ///< Stop an event
			void setChannel3dPosition(int nChannelId, const Vector3& vPosition); ///< Set a channels position in 3D space
			void setChannelVolume(int nChannelId, float fVolumedB); ///< Set the channel volume
			bool isEventPlaying(const string& strEventName) const; ///< Check if an event is playing
			FMOD_VECTOR static vectorToFmod(const Vector3& vPosition); ///< Convert position vector to FMOD
			float static dbToVolume(float dB); ///< Convert db to volume
			float static volumeTodB(float volume); ///< Convert volume to db
		};
	}
#endif
}

#define START_SOUND_ENGINE(...) Systems::Audio::start(__VA_ARGS__);
#define LOAD_SOUND_BANK(...) Systems::Audio::loadBank(__VA_ARGS__)
#define LOAD_SOUND(...) Systems::Audio::loadSound(__VA_ARGS__)
#define PLAY_SOUND(...) Systems::Audio::playSound(__VA_ARGS__)
#define UPDATE_SOUND_ENGINE(...) Systems::Audio::update(__VA_ARGS__);