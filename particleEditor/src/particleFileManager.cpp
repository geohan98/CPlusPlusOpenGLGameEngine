#include "particleFileManager.h"

namespace ParticleEditor {
	bool ParticleFileManager::save(Engine::ParticleSystemProperties* particleProperties, const char* filepath)
	{
		std::ofstream file(filepath, std::ios::out);

		if (file.is_open())
		{
			file << "spawnRate = " << particleProperties->m_spawnRate << std::endl;
			file << "minStartScale = " << particleProperties->m_minStartScale << std::endl;
			file << "maxStartScale = " << particleProperties->m_maxStartScale << std::endl;
			file << "minStartRotation = " << particleProperties->m_minStartRotation << std::endl;
			file << "maxStartRotation = " << particleProperties->m_maxStartRotation << std::endl;
			file << "minStartLinearVelocityX = " << particleProperties->m_minStartLinearVelocity.x << std::endl;
			file << "minStartLinearVelocityY = " << particleProperties->m_minStartLinearVelocity.y << std::endl;
			file << "minStartLinearVelocityZ = " << particleProperties->m_minStartLinearVelocity.z << std::endl;
			file << "maxStartLinearVelocityX = " << particleProperties->m_maxStartLinearVelocity.x << std::endl;
			file << "maxStartLinearVelocityY = " << particleProperties->m_maxStartLinearVelocity.y << std::endl;
			file << "maxStartLinearVelocityZ = " << particleProperties->m_maxStartLinearVelocity.z << std::endl;
			file << "minStartLifetime = " << particleProperties->m_minStartLifetime << std::endl;
			file << "maxStartLifetime = " << particleProperties->m_maxStartLifetime << std::endl;
			file << "minStartColourX = " << particleProperties->m_minStartColour.x << std::endl;
			file << "minStartColourY = " << particleProperties->m_minStartColour.y << std::endl;
			file << "minStartColourZ = " << particleProperties->m_minStartColour.z << std::endl;
			file << "minStartColourW = " << particleProperties->m_minStartColour.w << std::endl;
			file << "maxStartColourX = " << particleProperties->m_maxStartColour.x << std::endl;
			file << "maxStartColourY = " << particleProperties->m_maxStartColour.y << std::endl;
			file << "maxStartColourZ = " << particleProperties->m_maxStartColour.z << std::endl;
			file << "maxStartColourW = " << particleProperties->m_maxStartColour.w << std::endl;
			file << "minStartAngularVelocity = " << particleProperties->m_minStartAngularVelocity << std::endl;
			file << "maxStartAngularVelocity = " << particleProperties->m_maxStartAngularVelocity << std::endl;
			file << "minEndScale = " << particleProperties->m_minEndScale << std::endl;
			file << "maxEndScale = " << particleProperties->m_maxEndScale << std::endl;
			file << "minEndColourX = " << particleProperties->m_minEndColour.x << std::endl;
			file << "minEndColourY = " << particleProperties->m_minEndColour.y << std::endl;
			file << "minEndColourZ = " << particleProperties->m_minEndColour.z << std::endl;
			file << "minEndColourW = " << particleProperties->m_minEndColour.w << std::endl;
			file << "maxEndColourX = " << particleProperties->m_maxEndColour.x << std::endl;
			file << "maxEndColourY = " << particleProperties->m_maxEndColour.y << std::endl;
			file << "maxEndColourZ = " << particleProperties->m_maxEndColour.z << std::endl;
			file << "maxEndColourW = " << particleProperties->m_maxEndColour.w << std::endl;

			file.close();
			return true;
		}
		else return false;
	}
}