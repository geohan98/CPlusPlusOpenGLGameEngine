#pragma once

#include "include/independent/systems/events/event.h"

class WindowClose : Event
{
public:
	WindowClose() {};
	EventType getEventType() const override { return EventType::WindowClose; }
	int getCategoryFlags() const override { return EventCategoryWindow; }
};