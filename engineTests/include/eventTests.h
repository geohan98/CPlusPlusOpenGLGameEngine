#pragma once

#include <gtest/gtest.h>

#include "events/event.h"
#include "events/applicationEvents.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
#include "systems/ButtonCodes.h"

bool onResizeTrue(Engine::Events::WindowResize& e)
{
	return true;
}

bool onResizeFalse(Engine::Events::WindowResize& e)
{
	return false;
}

