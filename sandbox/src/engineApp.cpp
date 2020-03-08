/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <memory>
#include "gameLayer.h"
#include "imguiLayer.h"


engineApp::engineApp()
{
	LOG_INFO("[TANKS][START]");
	m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::GameLayer()));
}

engineApp::~engineApp()
{
	LOG_INFO("[TANKS][STOP]");
}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}