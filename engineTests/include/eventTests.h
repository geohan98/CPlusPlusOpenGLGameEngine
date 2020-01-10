#pragma once

#include <gtest/gtest.h>

#include "events/event.h"
#include "events/applicationEvents.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
#include "systems/ButtonCodes.h"

bool onResizeTrue(Engine::WindowResize& e)
{
	return true;
}

bool onResizeFalse(Engine::WindowResize& e)
{
	return false;
}

