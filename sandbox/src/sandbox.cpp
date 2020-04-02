/** \file Sandbox.cpp
*/
#include "sandbox.h"

#include "gameLayer.h"
#include "meshLayer.h"
#include "imguiLayer.h"

Sandbox::Sandbox(char* _name) : Engine::Application(_name)
{
	LOG_INFO("[{0}][START]", _name);
	//m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::GameLayer()));
	m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::MeshLayer()));
	//m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::ImGUILayer()));
}

Sandbox::~Sandbox()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Sandbox("SANDBOX");
}