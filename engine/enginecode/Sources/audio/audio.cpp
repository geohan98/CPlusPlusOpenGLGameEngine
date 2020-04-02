#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/audio/audio.h"
#include <fmod_errors.h>

namespace Engine {
	namespace Systems {
		AudioImplementation::AudioImplementation() {
			fmodStudioSystem = NULL;
			Audio::errorCheck(FMOD::Studio::System::create(&fmodStudioSystem));
			Audio::errorCheck(fmodStudioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));

#ifdef NG_DEBUG
			unsigned int version;
			Audio::errorCheck(FMOD::System_Create(&fmodSystem));
			Audio::errorCheck(fmodSystem->getVersion(&version));

			if (version < FMOD_VERSION) {
				LOG_CORE_INFO("FMOD LIB DOESN'T MATCH HEADER VERSION");
			}
#endif
			Audio::errorCheck(fmodSystem->init(32, FMOD_INIT_NORMAL, NULL));
			Audio::errorCheck(fmodSystem->set3DSettings(1.f, 1.f, 1.f));
			Audio::errorCheck(fmodSystem->setGeometrySettings(50.f));
		}

		void AudioImplementation::update() {
			vector<fmodChannelMap::iterator> pStoppedChannels;
			for (auto it = fmodChannels.begin(), itEnd = fmodChannels.end(); it != itEnd; ++it)
			{
				bool bIsPlaying = false;
				it->second->isPlaying(&bIsPlaying);
				if (!bIsPlaying)
				{
					pStoppedChannels.push_back(it);
				}
			}
			for (auto& it : pStoppedChannels)
			{
				fmodChannels.erase(it);
			}

			Audio::errorCheck(fmodStudioSystem->update());
		}

		AudioImplementation* sgpImplementation = nullptr;

		void Audio::start(SystemSignal init, ...)
		{
			sgpImplementation = new AudioImplementation;

			LOAD_SOUND_BANK("assets/audio/master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
			LOAD_SOUND_BANK("assets/audio/master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		}

		void Audio::stop(SystemSignal close, ...)
		{
			delete sgpImplementation;
		}

		void Audio::update()
		{
			sgpImplementation->update();
		}

		void Audio::loadSound(const std::string& stringSoundName, bool b3d, bool bLooping, bool bStream)
		{
			auto foundEvent = sgpImplementation->fmodSounds.find(stringSoundName);
			
			if (foundEvent != sgpImplementation->fmodSounds.end())
				return;
			
			FMOD_MODE eMode = FMOD_DEFAULT; 
			eMode |= b3d ? FMOD_3D : FMOD_2D;
			eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
			eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
			FMOD::Sound* pSound = nullptr;
			
			Audio::errorCheck(sgpImplementation->fmodSystem->createSound(stringSoundName.c_str(), eMode, nullptr, &pSound));
			
			if (pSound) {
				sgpImplementation->fmodSounds[stringSoundName] = pSound;
			}
		}

		void Audio::unLoadSound(const std::string& stringSoundName)
		{
			auto foundEvent = sgpImplementation->fmodSounds.find(stringSoundName);
			
			if (foundEvent == sgpImplementation->fmodSounds.end())
				return;
			
			Audio::errorCheck(foundEvent->second->release());
			
			sgpImplementation->fmodSounds.erase(foundEvent);
		}

		int Audio::playSound(const string& stringSoundName, const Vector3& vPosition, float fVolumedB)
		{
			int nChannelId = sgpImplementation->fmodNextChannelId++;
			
			auto foundEvent = sgpImplementation->fmodSounds.find(stringSoundName);
			
			if (foundEvent == sgpImplementation->fmodSounds.end())
			{
				loadSound(stringSoundName);
				foundEvent = sgpImplementation->fmodSounds.find(stringSoundName);
				if (foundEvent == sgpImplementation->fmodSounds.end())
				{
					return nChannelId;
				}
			}
			
			FMOD::Channel* pChannel = nullptr;
			
			Audio::errorCheck(sgpImplementation->fmodSystem->playSound(foundEvent->second, nullptr, true, &pChannel));
			if (pChannel)
			{
				FMOD_MODE currentMode;
				foundEvent->second->getMode(&currentMode);

				if (currentMode & FMOD_3D) {
					FMOD_VECTOR position = vectorToFmod(vPosition);
					Audio::errorCheck(pChannel->set3DAttributes(&position, nullptr));
				}

				Audio::errorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
				Audio::errorCheck(pChannel->setPaused(false));
				sgpImplementation->fmodChannels[nChannelId] = pChannel;
			}
			return nChannelId;
		}

		void Audio::setChannel3dPosition(int nChannelId, const Vector3& vPosition)
		{
			auto foundEvent = sgpImplementation->fmodChannels.find(nChannelId);

			if (foundEvent == sgpImplementation->fmodChannels.end())
				return;

			FMOD_VECTOR position = vectorToFmod(vPosition);

			foundEvent->second->set3DAttributes(&position, NULL);
		}

		void Audio::setChannelVolume(int nChannelId, float fVolumedB)
		{
			auto foundEvent = sgpImplementation->fmodChannels.find(nChannelId);

			if (foundEvent == sgpImplementation->fmodChannels.end())
				return;

			foundEvent->second->setVolume(dbToVolume(fVolumedB));
		}

		void Audio::loadBank(const std::string& stringBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
			auto foundEvent = sgpImplementation->fmodBanks.find(stringBankName);

			if (foundEvent != sgpImplementation->fmodBanks.end())
				return;

			FMOD::Studio::Bank* pBank;

			Audio::errorCheck(sgpImplementation->fmodStudioSystem->loadBankFile(stringBankName.c_str(), flags, &pBank));

			if (pBank) {
				sgpImplementation->fmodBanks[stringBankName] = pBank;
			}
		}

		void Audio::loadEvent(const std::string& stringEventName) {
			auto foundEvent = sgpImplementation->fmodEvents.find(stringEventName);

			if (foundEvent != sgpImplementation->fmodEvents.end())
				return;

			FMOD::Studio::EventDescription* pEventDescription = NULL;
			
			Audio::errorCheck(sgpImplementation->fmodStudioSystem->getEvent(stringEventName.c_str(), &pEventDescription));		
			if (pEventDescription) {
				FMOD::Studio::EventInstance* pEventInstance = NULL;
				Audio::errorCheck(pEventDescription->createInstance(&pEventInstance));
				if (pEventInstance) {
					sgpImplementation->fmodEvents[stringEventName] = pEventInstance;
				}
			}
		}

		void Audio::playEvent(const string &stringEventName) {
			auto foundEvent = sgpImplementation->fmodEvents.find(stringEventName);
			if (foundEvent == sgpImplementation->fmodEvents.end()) {
				loadEvent(stringEventName);
				foundEvent = sgpImplementation->fmodEvents.find(stringEventName);
				if (foundEvent == sgpImplementation->fmodEvents.end())
					return;
			}
			foundEvent->second->start();
		}

		void Audio::stopEvent(const string &stringEventName, bool bImmediate) {
			auto foundEvent = sgpImplementation->fmodEvents.find(stringEventName);
			if (foundEvent == sgpImplementation->fmodEvents.end())
				return;
			FMOD_STUDIO_STOP_MODE eMode;
			eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
			Audio::errorCheck(foundEvent->second->stop(eMode));
		}

		bool Audio::isEventPlaying(const string &stringEventName) const {
			auto foundEvent = sgpImplementation->fmodEvents.find(stringEventName);
			if (foundEvent == sgpImplementation->fmodEvents.end())
				return false;

			FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
			if (foundEvent->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
				return true;
			}
			return false;
		}

		void Audio::getEventParameter(const string &stringEventName, const string &stringParameterName, float* parameter) {
			auto foundEvent = sgpImplementation->fmodEvents.find(stringEventName);
			if (foundEvent == sgpImplementation->fmodEvents.end())
				return;
		}

		void Audio::setEventParameter(const string &stringEventName, const string &stringParameterName, float fValue) {
			auto foundEvent = sgpImplementation->fmodEvents.find(stringEventName);
			if (foundEvent == sgpImplementation->fmodEvents.end())
				return;
		}

		FMOD_VECTOR Audio::vectorToFmod(const Vector3& vPosition) {
			FMOD_VECTOR fVec;
			fVec.x = vPosition.x;
			fVec.y = vPosition.y;
			fVec.z = vPosition.z;
			return fVec;
		}

		int Audio::errorCheck(FMOD_RESULT result) {
			if (result != FMOD_OK) {
				cout << "Audio::errorCheck: FMOD ERROR " << result << endl;
				return 1;
			}
			return 0;
		}

		float  Audio::dbToVolume(float dB)
		{
			return powf(10.0f, 0.05f * dB);
		}

		float  Audio::volumeTodB(float vol)
		{
			return 20.0f * log10f(vol);
		}
	}
}