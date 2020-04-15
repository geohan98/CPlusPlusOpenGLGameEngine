#pragma once

#include <Engine.h>

namespace ParticleEditor
{
	class ParticleEditor : public Engine::Application
	{
	private:
		std::shared_ptr<Engine::Layer> m_uiLayer;
		std::shared_ptr<Engine::Layer> m_sceneLayer;
	public:
		ParticleEditor(char* _name);
		~ParticleEditor() override;
	};
}
