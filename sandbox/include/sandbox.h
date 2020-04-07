#pragma once

#include <Engine.h>

class Sandbox : public Engine::Application
{
public:
	Sandbox(char* _name);
	~Sandbox() override;

	inline void buttonClickedExample() {
		std::cout << "Sandbox button clicked" << std::endl;
	}
};
