#pragma once

#include <gtest/gtest.h>

#include "Headers/events/event.h"
#include "Headers/events/applicationEvents.h"
#include "Headers/events/keyEvents.h"
#include "Headers/events/mouseEvents.h"
#include "Headers/systems/ButtonCodes.h"

bool onResizeTrue(Engine::Events::WindowResize& e)
{
	return true;
}

bool onResizeFalse(Engine::Events::WindowResize& e)
{
	return false;
}

