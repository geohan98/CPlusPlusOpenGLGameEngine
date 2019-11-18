#pragma once

#include <gtest/gtest.h>

#include "systems/events/event.h"
#include "systems/events/applicationEvents.h"

bool onResizeTrue(Engine::WindowResize& e)
{
	return true;
}

bool onResizeFalse(Engine::WindowResize& e)
{
	return false;
}