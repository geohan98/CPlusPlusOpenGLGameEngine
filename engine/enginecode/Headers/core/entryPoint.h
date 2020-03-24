#pragma once
/** \file entryPoint.h
*/


#include "../enginecode/Headers/core/application.h"
#include <crtdbg.h>


extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	auto application = Engine::startApplication();
	application->run();
	delete application;

	//_CrtDumpMemoryLeaks();
	return 0;
}

