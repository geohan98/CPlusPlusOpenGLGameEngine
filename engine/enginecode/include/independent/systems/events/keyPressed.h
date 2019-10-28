#pragma once

#include "include/independent/systems/events/event.h"

class KeyPressed : public Event
{
public:
	KeyPressed(int button, int repeatCode);
	static EventType getStaticType() { return EventType::KeyPressed; }
	EventType getEventType() const override { return EventType::KeyPressed; }
	int getCategoryFlags() const override { return EventCategoryKeyboard; }
};