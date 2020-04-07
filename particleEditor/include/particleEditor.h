#pragma once

#include <Engine.h>

namespace ParticleEditor
{
	class ParticleEditor : public Engine::Application
	{
	public:
		ParticleEditor(char* _name);
		~ParticleEditor() override;
	};
}
