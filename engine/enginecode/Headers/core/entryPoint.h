#pragma once
/** \file entryPoint.h
*/

#include "../enginecode/Headers/core/application.h"


extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	auto application = Engine::startApplication();
	application->run();
	delete application;
	return 0;
}

