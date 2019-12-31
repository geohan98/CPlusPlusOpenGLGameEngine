/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <memory>
#include "core/gameLayer.h"


engineApp::engineApp()
{
	m_layerStack->push(std::shared_ptr<Engine::GameLayer>(new Engine::GameLayer()));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{

	return new engineApp();
}