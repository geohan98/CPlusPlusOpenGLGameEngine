/** \file Sandbox.cpp
*/
#include "sandbox.h"
#include "meshLayer.h"
#include "imguiLayer.h"

Sandbox::Sandbox(char* _name) : Engine::Application(_name)
{
	LOG_INFO("[{0}][START]", _name);
	m_meshLayer = m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::MeshLayer));
	m_imGuiLayer = m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::ImGUILayer));

	m_imGuiLayer->addSubscriber(m_meshLayer);
}

Sandbox::~Sandbox()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Sandbox("SANDBOX");
}