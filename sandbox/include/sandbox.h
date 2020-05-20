#pragma once

#include <Engine.h>

class Sandbox : public Engine::Application
{
private:
	std::shared_ptr<Engine::Layer> m_meshLayer;
	std::shared_ptr<Engine::Layer> m_imGuiLayer;
public:
	Sandbox(char* _name);
	~Sandbox() override;
};
