#pragma once

#include <Engine.h>

namespace ParticleEditor
{
	class ParticleEditor : public Engine::Application
	{
	private:
		std::shared_ptr<Engine::Layer> m_uiLayer; ///< The ui layer of the particle editor
		std::shared_ptr<Engine::Layer> m_sceneLayer; ///< The scene layer for the particle editor, this is where the particle compionet is
	public:
		ParticleEditor(char* _name); ///< Constructor
		~ParticleEditor() override; ///< Destructor
	}
}