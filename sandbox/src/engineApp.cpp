/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <memory>
#include "core/gameLayer.h"
#include "core/layer2D.h"


engineApp::engineApp()
{
	m_layerStack->push(std::shared_ptr<Engine::GameLayer>(new Engine::GameLayer()));
	m_layerStack->push(std::shared_ptr<Engine::Layer2D>(new Engine::Layer2D()));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{

	return new engineApp();
}