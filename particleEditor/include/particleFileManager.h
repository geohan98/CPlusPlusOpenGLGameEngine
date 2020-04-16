#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Headers/components/particleComponent.h"
#include "Headers/systems/log.h"

namespace ParticleEditor
{
	class ParticleFileManager {
		public:	
			static bool save(Engine::ParticleSystemProperties* particleProperties, const char* filepath);
	};
}