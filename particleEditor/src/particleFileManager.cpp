#include "particleFileManager.h"

namespace ParticleEditor {
	bool ParticleFileManager::save(Engine::ParticleSystemProperties* particleProperties, const char* filepath)
	{
		std::ofstream file(filepath, std::ios::out);

		if (file.is_open())
		{
			file << "spawnRate=" << particleProperties->m_spawnRate << std::endl <<
			"minStartScale=" << particleProperties->m_minStartScale << std::endl <<
			"maxStartScale=" << particleProperties->m_maxStartScale << std::endl <<
			"minStartRotation=" << particleProperties->m_minStartRotation << std::endl <<
			"maxStartRotation=" << particleProperties->m_maxStartRotation << std::endl <<
			"minStartLinearVelocityX=" << particleProperties->m_minStartLinearVelocity.x << std::endl <<
			"minStartLinearVelocityY=" << particleProperties->m_minStartLinearVelocity.y << std::endl << 
			"minStartLinearVelocityZ=" << particleProperties->m_minStartLinearVelocity.z << std::endl <<
			"maxStartLinearVelocityX=" << particleProperties->m_maxStartLinearVelocity.x << std::endl <<
			"maxStartLinearVelocityY=" << particleProperties->m_maxStartLinearVelocity.y << std::endl <<
			"maxStartLinearVelocityZ=" << particleProperties->m_maxStartLinearVelocity.z << std::endl <<
			"minStartLifetime=" << particleProperties->m_minStartLifetime << std::endl <<
			"maxStartLifetime=" << particleProperties->m_maxStartLifetime << std::endl <<
			"minStartColourX=" << particleProperties->m_minStartColour.x << std::endl <<
			"minStartColourY=" << particleProperties->m_minStartColour.y << std::endl <<
			"minStartColourZ=" << particleProperties->m_minStartColour.z << std::endl <<
			"minStartColourW=" << particleProperties->m_minStartColour.w << std::endl <<
			"maxStartColourX=" << particleProperties->m_maxStartColour.x << std::endl <<
			"maxStartColourY=" << particleProperties->m_maxStartColour.y << std::endl <<
			"maxStartColourZ=" << particleProperties->m_maxStartColour.z << std::endl <<
			"maxStartColourW=" << particleProperties->m_maxStartColour.w << std::endl <<
			"minStartAngularVelocity=" << particleProperties->m_minStartAngularVelocity << std::endl <<
			"maxStartAngularVelocity=" << particleProperties->m_maxStartAngularVelocity << std::endl <<
			"minEndScale=" << particleProperties->m_minEndScale << std::endl <<
			"maxEndScale=" << particleProperties->m_maxEndScale << std::endl <<
			"minEndColourX=" << particleProperties->m_minEndColour.x << std::endl <<
			"minEndColourY=" << particleProperties->m_minEndColour.y << std::endl <<
			"minEndColourZ=" << particleProperties->m_minEndColour.z << std::endl <<
			"minEndColourW=" << particleProperties->m_minEndColour.w << std::endl <<
			"maxEndColourX=" << particleProperties->m_maxEndColour.x << std::endl <<
			"maxEndColourY=" << particleProperties->m_maxEndColour.y << std::endl <<
			"maxEndColourZ=" << particleProperties->m_maxEndColour.z << std::endl <<
			"maxEndColourW=" << particleProperties->m_maxEndColour.w << std::endl;

			file.close();
			return true;
		}
		else return false;
	}
	Engine::ParticleSystemProperties * ParticleFileManager::load(const char * filepath)
	{
		Engine::ParticleSystemProperties* properties = new Engine::ParticleSystemProperties;
		std::ifstream file(filepath);
			
		Engine::IniParser particleFile = Engine::IniParser(filepath);
		properties->m_spawnRate = particleFile.getDataFloat("spawnRate");
		properties->m_minStartScale = particleFile.getDataFloat("minStartScale");
		properties->m_maxStartScale = particleFile.getDataFloat("maxStartScale");
		properties->m_minStartRotation = particleFile.getDataFloat("minStartRotation");
		properties->m_maxStartRotation = particleFile.getDataFloat("maxStartRotation");
		properties->m_minStartLinearVelocity.x = particleFile.getDataFloat("minStartLinearVelocityX");
		properties->m_minStartLinearVelocity.y = particleFile.getDataFloat("minStartLinearVelocityY");
		properties->m_minStartLinearVelocity.z = particleFile.getDataFloat("minStartLinearVelocityZ");
		properties->m_maxStartLinearVelocity.x = particleFile.getDataFloat("maxStartLinearVelocityX");
		properties->m_maxStartLinearVelocity.y = particleFile.getDataFloat("maxStartLinearVelocityY");
		properties->m_maxStartLinearVelocity.z = particleFile.getDataFloat("maxStartLinearVelocityZ");
		properties->m_minStartLifetime = particleFile.getDataFloat("minStartLifetime");
		properties->m_maxStartLifetime = particleFile.getDataFloat("maxStartLifetime");
		properties->m_minStartColour.x = particleFile.getDataFloat("minStartColourX");
		properties->m_minStartColour.y = particleFile.getDataFloat("minStartColourY");
		properties->m_minStartColour.z = particleFile.getDataFloat("minStartColourZ");
		properties->m_minStartColour.w = particleFile.getDataFloat("minStartColourW");
		properties->m_maxStartColour.x = particleFile.getDataFloat("maxStartColourX");
		properties->m_maxStartColour.y = particleFile.getDataFloat("maxStartColourY");
		properties->m_maxStartColour.z = particleFile.getDataFloat("maxStartColourZ");
		properties->m_maxStartColour.w = particleFile.getDataFloat("maxStartColourW");
		properties->m_minStartAngularVelocity = particleFile.getDataFloat("minStartAngularVelocity");
		properties->m_maxStartAngularVelocity = particleFile.getDataFloat("maxStartAngularVelocity");
		properties->m_minEndScale = particleFile.getDataFloat("minEndScale");
		properties->m_maxEndScale = particleFile.getDataFloat("maxEndScale");
		properties->m_minEndColour.x = particleFile.getDataFloat("minEndColourX");
		properties->m_minEndColour.y = particleFile.getDataFloat("minEndColourY");
		properties->m_minEndColour.z = particleFile.getDataFloat("minEndColourZ");
		properties->m_minEndColour.w = particleFile.getDataFloat("minEndColourW");
		properties->m_maxEndColour.x = particleFile.getDataFloat("maxEndColourX");
		properties->m_maxEndColour.y = particleFile.getDataFloat("maxEndColourY");
		properties->m_maxEndColour.z = particleFile.getDataFloat("maxEndColourZ");
		properties->m_maxEndColour.w = particleFile.getDataFloat("maxEndColourW");
		
		return properties;
	}
}