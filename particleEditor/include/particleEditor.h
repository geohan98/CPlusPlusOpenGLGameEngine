#pragma once

#include <Engine.h>

namespace ParticleDesigner
{
	class ParticleEditor : public Engine::Application
	{
	public:
		ParticleEditor(char* _name);
		~ParticleEditor() override;
	};
}
