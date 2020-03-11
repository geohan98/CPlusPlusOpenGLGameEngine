#pragma once

#include <Engine.h>

class Game : public Engine::Application
{
public:
	Game(char* _name, int _width, int _height);
	~Game() override;
};
