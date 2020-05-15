/** \file Sandbox.cpp
*/
#include "sandbox.h"

#include "gameLayer.h"
#include "meshLayer.h"
#include "imguiLayer.h"
#include "layer2D.h"
#include "uiButtons.h"

Sandbox::Sandbox(char* _name) : Engine::Application(_name)
{
	LOG_INFO("[{0}][START]", _name);
	//m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::GameLayer()));
	m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::MeshLayer()));


	//Engine::ImGUILayer* imGuiInstance = new Engine::ImGUILayer();
	//::uiButtons* uibuttonsInstance = new Engine::uiButtons();
	//m_layerStack->push(std::shared_ptr<Engine::Layer>(imGuiInstance));
	//m_layerStack->push(std::shared_ptr<Engine::Layer>(uibuttonsInstance));


	//m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::Layer2D));

	//imGuiInstance->createButton("1", { 100, 50 }, { 100, 100 }, "pos(100,100) button", ImVec4(0.8f, 0.4f, 1.0f, 1.0f), -1, [this] { buttonClickedExample(); });
	//uibuttonsInstance->createButton(0, { 100, 80 },  "assets/textures/buttonShiny.png", { 100, 50}, 0);
	//uibuttonsInstance->createButton(1, { 300, 80 }, "assets/textures/buttonTest.png", { 100, 50 }, 2);
	//uibuttonsInstance->createButton(0, { 160, 80 }, "assets/textures/buttonTest.png", { 500, 500 }, 1);

	//std::unordered_map < std::string, unsigned int> fonts;
	//fonts.emplace(std::pair<std::string, unsigned int>("assets/fonts/Roboto-Medium.ttf", 48));

	//m_resourceManager->populateCharacters(fonts);
}

Sandbox::~Sandbox()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Sandbox("SANDBOX");
}