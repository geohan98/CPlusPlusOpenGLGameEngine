/** \file Game.cpp
*/
#include "game.h"

Game::Game(char* _name, int _width, int _height) : Engine::Application(_name, _width, _height)
{
	LOG_INFO("[{0}][START]", _name);
}

Game::~Game()
{
	LOG_INFO("ENGINE APP: STOP");
}

Engine::Application* Engine::startApplication()
{
	return new Game("GAME", 1280, 720);
}