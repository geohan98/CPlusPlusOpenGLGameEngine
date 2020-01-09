/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <memory>
#include "layers/gameLayer.h"
#include "layers/layer2D.h"
#include "layers/JSONLayer.h"


engineApp::engineApp()
{
	m_layerStack->push(std::shared_ptr<Engine::JSONLayer>(new Engine::JSONLayer("assets/levels/cubeLevel.json")));
	//m_layerStack->push(std::shared_ptr<Engine::GameLayer>(new Engine::GameLayer()));
	m_layerStack->push(std::shared_ptr<Engine::Layer2D>(new Engine::Layer2D()));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{

	return new engineApp();
}