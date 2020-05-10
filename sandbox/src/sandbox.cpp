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
	m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::MeshLayer()));
	m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::uiButtons()));

	Engine::ImGUILayer* imGuiInstance = new Engine::ImGUILayer();
	m_layerStack->push(std::shared_ptr<Engine::Layer>(imGuiInstance));
	imGuiInstance->createButton("1", { 100, 50 }, { 100, 100 }, "pos(100,100) button", ImVec4(0.8f, 0.4f, 1.0f, 1.0f), -1, [this] { buttonClickedExample(); });
}

Sandbox::~Sandbox()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Sandbox("SANDBOX");
}