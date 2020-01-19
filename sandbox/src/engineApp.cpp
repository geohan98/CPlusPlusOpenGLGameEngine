/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <memory>
#include "gameLayer.h"


engineApp::engineApp()
{
	LOG_INFO("ENGINE APP: START");
	m_layerStack->push(std::shared_ptr<Engine::GameLayer>(new Engine::GameLayer()));
}

engineApp::~engineApp()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}