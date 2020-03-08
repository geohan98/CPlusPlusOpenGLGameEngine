/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <memory>
#include "gameLayer.h"
#include "imguiLayer.h"
#include "audioLayer.h"
#include "layer2D.h"


engineApp::engineApp()
{
	LOG_INFO("ENGINE APP: START");
	m_layerStack->push(std::shared_ptr<Engine::GameLayer>(new Engine::GameLayer()));
	m_layerStack->push(std::shared_ptr<Engine::ImGUILayer>(new Engine::ImGUILayer()));
	m_layerStack->push(std::shared_ptr<Engine::AudioLayer>(new Engine::AudioLayer()));
}

engineApp::~engineApp()
{
	LOG_INFO("[TANKS][STOP]");
}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}