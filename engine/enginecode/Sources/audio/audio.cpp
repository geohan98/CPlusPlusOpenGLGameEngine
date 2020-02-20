#include "engine_pch.h"

#include "../enginecode/Headers/systems/log.h"

#include "../enginecode/Headers/audio/audio.h"
#include <fmod_errors.h>

namespace Engine {
	namespace Systems {
		Implementation::Implementation() {
			mpStudioSystem = NULL;
			Audio::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
			Audio::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));

			unsigned int version;
			Audio::ErrorCheck(FMOD::System_Create(&mpSystem));
			Audio::ErrorCheck(mpSystem->getVersion(&version));

			if (version < FMOD_VERSION) {
				LOG_CORE_INFO("FMOD LIB DOESN'T MATCH HEADER VERSION");
			}

			Audio::ErrorCheck(mpSystem->init(32, FMOD_INIT_NORMAL, NULL));
			Audio::ErrorCheck(mpSystem->set3DSettings(1.f, 1.f, 1.f));
			Audio::ErrorCheck(mpSystem->setGeometrySettings(50.f));
		}

		Implementation::~Implementation() {
			Audio::ErrorCheck(mpStudioSystem->unloadAll());
			Audio::ErrorCheck(mpStudioSystem->release());
		}

		void Implementation::Update() {
			vector<ChannelMap::iterator> pStoppedChannels;
			for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
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
				mChannels.erase(it);
			}

			Audio::ErrorCheck(mpStudioSystem->update());
		}

		Implementation* sgpImplementation = nullptr;

		void Audio::start(SystemSignal init, ...)
		{
			sgpImplementation = new Implementation;
		}

		void Audio::stop(SystemSignal close, ...)
		{
			delete sgpImplementation;
		}

		void Audio::Update()
		{
			sgpImplementation->Update();
		}

		void Audio::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
		{
			auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
			if (tFoundIt != sgpImplementation->mSounds.end())
				return;
			FMOD_MODE eMode = FMOD_DEFAULT;
			eMode |= b3d ? FMOD_3D : FMOD_2D;
			eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
			eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
			FMOD::Sound* pSound = nullptr;
			Audio::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
			if (pSound) {
				sgpImplementation->mSounds[strSoundName] = pSound;
			}
		}

		void Audio::UnLoadSound(const std::string& strSoundName)
		{
			auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
			if (tFoundIt == sgpImplementation->mSounds.end())
				return;
			Audio::ErrorCheck(tFoundIt->second->release());
			sgpImplementation->mSounds.erase(tFoundIt);
		}

		int Audio::PlaySounds(const string& strSoundName, const Vector3& vPosition, float fVolumedB)
		{
			int nChannelId = sgpImplementation->mnNextChannelId++;
			auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
			if (tFoundIt == sgpImplementation->mSounds.end())
			{
				LoadSound(strSoundName);
				tFoundIt = sgpImplementation->mSounds.find(strSoundName);
				if (tFoundIt == sgpImplementation->mSounds.end())
				{
					return nChannelId;
				}
			}
			FMOD::Channel* pChannel = nullptr;
			Audio::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
			if (pChannel)
			{
				FMOD_MODE currMode;
				tFoundIt->second->getMode(&currMode);
				if (currMode & FMOD_3D) {
					FMOD_VECTOR position = VectorToFmod(vPosition);
					Audio::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
				}
				Audio::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
				Audio::ErrorCheck(pChannel->setPaused(false));
				sgpImplementation->mChannels[nChannelId] = pChannel;
			}
			return nChannelId;
		}

		void Audio::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
		{
			auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
			if (tFoundIt == sgpImplementation->mChannels.end())
				return;

			FMOD_VECTOR position = VectorToFmod(vPosition);
			Audio::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
		}

		void Audio::SetChannelVolume(int nChannelId, float fVolumedB)
		{
			auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
			if (tFoundIt == sgpImplementation->mChannels.end())
				return;

			Audio::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
		}

		void Audio::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
			auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
			if (tFoundIt != sgpImplementation->mBanks.end())
				return;
			FMOD::Studio::Bank* pBank;
			Audio::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
			if (pBank) {
				sgpImplementation->mBanks[strBankName] = pBank;
			}
		}

		void Audio::LoadEvent(const std::string& strEventName) {
			auto tFoundit = sgpImplementation->mEvents.find(strEventName);
			if (tFoundit != sgpImplementation->mEvents.end())
				return;
			FMOD::Studio::EventDescription* pEventDescription = NULL;
			Audio::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
			if (pEventDescription) {
				FMOD::Studio::EventInstance* pEventInstance = NULL;
				Audio::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
				if (pEventInstance) {
					sgpImplementation->mEvents[strEventName] = pEventInstance;
				}
			}
		}

		void Audio::PlayEvent(const string &strEventName) {
			auto tFoundit = sgpImplementation->mEvents.find(strEventName);
			if (tFoundit == sgpImplementation->mEvents.end()) {
				LoadEvent(strEventName);
				tFoundit = sgpImplementation->mEvents.find(strEventName);
				if (tFoundit == sgpImplementation->mEvents.end())
					return;
			}
			tFoundit->second->start();
		}

		void Audio::StopEvent(const string &strEventName, bool bImmediate) {
			auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
			if (tFoundIt == sgpImplementation->mEvents.end())
				return;
			FMOD_STUDIO_STOP_MODE eMode;
			eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
			Audio::ErrorCheck(tFoundIt->second->stop(eMode));
		}

		bool Audio::IsEventPlaying(const string &strEventName) const {
			auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
			if (tFoundIt == sgpImplementation->mEvents.end())
				return false;

			FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
			if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
				return true;
			}
			return false;
		}

		void Audio::GetEventParameter(const string &strEventName, const string &strParameterName, float* parameter) {
			auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
			if (tFoundIt == sgpImplementation->mEvents.end())
				return;

			// REMOVED DUE TO PARAMETER INSTANCE NOT BEING A PART OF FMOD STUDIO
			//FMOD::Studio::ParameterInstance* pParameter = NULL;
			//Audio::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
			//Audio::ErrorCheck(pParameter->getValue(parameter));

		}

		void Audio::SetEventParameter(const string &strEventName, const string &strParameterName, float fValue) {
			auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
			if (tFoundIt == sgpImplementation->mEvents.end())
				return;

			// REMOVED DUE TO PARAMETER INSTANCE NOT BEING A PART OF FMOD STUDIO
			//FMOD::Studio::ParameterInstance* pParameter = NULL;
			//Audio::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
			//Audio::ErrorCheck(pParameter->setValue(fValue));
		}

		FMOD_VECTOR Audio::VectorToFmod(const Vector3& vPosition) {
			FMOD_VECTOR fVec;
			fVec.x = vPosition.x;
			fVec.y = vPosition.y;
			fVec.z = vPosition.z;
			return fVec;
		}

		int Audio::ErrorCheck(FMOD_RESULT result) {
			if (result != FMOD_OK) {
				cout << "FMOD ERROR " << result << endl;
				return 1;
			}
			// cout << "FMOD all good" << endl;
			return 0;
		}

		float  Audio::dbToVolume(float dB)
		{
			return powf(10.0f, 0.05f * dB);
		}

		float  Audio::VolumeTodB(float volume)
		{
			return 20.0f * log10f(volume);
		}

		//void Audio::Shutdown() {
		//	delete sgpImplementation;
		//}
	}
}