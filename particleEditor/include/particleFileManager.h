#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Headers/components/particleComponent.h"
#include "Headers/systems/log.h"
#include "Headers/fileLoaders/iniParser.h"

namespace ParticleEditor
{
	class ParticleFileManager {
	public:
		static bool save(Engine::ParticleSystemProperties* particleProperties, const char* filepath); ///< Save the current particle system properties to a file, at a specified filepath
		static Engine::ParticleSystemProperties* load(const char* filepath);///< Load particle system properties from a file, at a specified filepath
	};
}