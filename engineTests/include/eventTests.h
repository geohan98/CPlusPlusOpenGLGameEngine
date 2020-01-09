#pragma once

#include <gtest/gtest.h>

#include "events/event.h"
#include "events/applicationEvents.h"

bool onResizeTrue(Engine::WindowResize& e)
{
	return true;
}

bool onResizeFalse(Engine::WindowResize& e)
{
	return false;
}