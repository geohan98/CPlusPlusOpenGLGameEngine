/** \file Sandbox.cpp
*/
#include "sandbox.h"

Sandbox::Sandbox(char* _name, int _width, int _height) : Engine::Application(_name, _width, _height)
{
	LOG_INFO("[{0}][START]", _name);
}

Sandbox::~Sandbox()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Sandbox("SANDBOX", 1280, 720);
}