#include "gameApp.h"


GameApp::GameApp()
{
	LOG_TRACE("GAME APP: Starting App");
}

GameApp::~GameApp()
{
	LOG_TRACE("GAME APP: Closing App");
}

Engine::Application* Engine::startApplication()
{
	return new GameApp();
}