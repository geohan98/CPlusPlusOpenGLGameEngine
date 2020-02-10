#include "engine_pch.h"

/*#include "audio.h"
#include <fmod_errors.h>

namespace Engine {
	Implementation::Implementation() {
		mpStudioSystem = NULL;
		Audio::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
		Audio::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

		// REMOVED DUE TO GET LOW LEVEL SYSTEM NOT BEING A MEMBER FUNCTION OF mpStudioSystem
		mpSystem = NULL;
		//Audio::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));
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

	void Audio::Init() {
		sgpImplementation = new Implementation;
	}

	void Audio::Update() {
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

	void Audio::Shutdown() {
		delete sgpImplementation;
	}
}*/