#include "particleEditor.h"
#include "particleLayer.h"

namespace ParticleDesigner
{
	ParticleEditor::ParticleEditor(char* _name) : Engine::Application(_name)
	{
		LOG_INFO("[{0}][START]", _name);
		m_layerStack->push(std::shared_ptr<Engine::Layer>(new ParticleLayer()));
	}

	ParticleEditor::~ParticleEditor()
	{
		LOG_INFO("[PARTICLE DESIGNER][STOP]");
	}
}

Engine::Application* Engine::startApplication()
{
	return new ParticleDesigner::ParticleEditor("PARTICLE DESIGNER");
}