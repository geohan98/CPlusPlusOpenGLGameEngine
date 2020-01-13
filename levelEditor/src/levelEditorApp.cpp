#include "LevelEditorApp.h"
#include "systems/log.h"


LevelEditorApp::LevelEditorApp()
{
	LOG_TRACE("LEVEL EDITOR APP: Starting App");
}

LevelEditorApp::~LevelEditorApp()
{
	LOG_TRACE("LEVEL EDITOR APP: Closing App");
}

Engine::Application* Engine::startApplication()
{
	return new LevelEditorApp();
}