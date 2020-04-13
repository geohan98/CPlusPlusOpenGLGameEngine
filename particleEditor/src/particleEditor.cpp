#include "particleEditor.h"
#include "particleLayer.h"
#include "editorImGUILayer.h"

namespace ParticleEditor
{
	ParticleEditor::ParticleEditor(char* _name) : Engine::Application(_name)
	{
		LOG_INFO("[{0}][START]", _name);
		m_layerStack->push(std::shared_ptr<Engine::Layer>(new ParticleLayer()));
		m_layerStack->push(std::shared_ptr<Engine::Layer>(new EditorImGuiLayer()));

		(*(m_layerStack->begin() + 1))->addSubscriber(&(*(*m_layerStack->begin())));
	}

	ParticleEditor::~ParticleEditor()
	{
		LOG_INFO("[PARTICLE DESIGNER][STOP]");
	}
}

Engine::Application* Engine::startApplication()
{
	return new ParticleEditor::ParticleEditor("PARTICLE EDITOR");
}