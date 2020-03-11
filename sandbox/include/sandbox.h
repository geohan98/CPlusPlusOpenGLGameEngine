#pragma once

#include <Engine.h>

class Sandbox : public Engine::Application
{
public:
	Sandbox(char* _name, int _width, int _height);
	~Sandbox() override;
};
