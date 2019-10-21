#pragma once

#include "include/independent/systems/events/event.h"

class KeyPressed : Event
{
public:
	KeyPressed(int button, int repeatCode);
	EventType getEventType() const override { return EventType::KeyPressed; }
	int getCategoryFlags() const override { return EventCategoryKeyboard; }
};