/** \file Sandbox.cpp
*/
#include "sandbox.h"

#include "gameLayer.h"
#include "meshLayer.h"

Sandbox::Sandbox(char* _name, int _width, int _height) : Engine::Application(_name, _width, _height)
{
	LOG_INFO("[{0}][START]", _name);
	//m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::GameLayer()));
	m_layerStack->push(std::shared_ptr<Engine::Layer>(new Engine::MeshLayer()));
}

Sandbox::~Sandbox()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Sandbox("SANDBOX", 1280, 720);
}