#include "particleEditor.h"
#include "particleLayer.h"
#include "editorImGUILayer.h"

namespace ParticleEditor
{
	ParticleEditor::ParticleEditor(char* _name) : Engine::Application(_name)
	{
		LOG_INFO("[{0}][START]", _name);
		m_sceneLayer = std::shared_ptr<Engine::Layer>(new ParticleLayer());
		m_layerStack->push(m_sceneLayer);
		m_uiLayer = std::shared_ptr<Engine::Layer>(new EditorImGuiLayer());
		m_layerStack->push(m_uiLayer);

		m_uiLayer->addSubscriber(m_sceneLayer);

		std::unordered_map < std::string, unsigned int> fonts;
		fonts.emplace(std::pair<std::string, unsigned int>("assets/fonts/Roboto-Medium.ttf", 8));

		m_resourceManager->populateCharacters(fonts);
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