#pragma once

#include "include/independent/systems/events/event.h"

class WindowClose : public Event
{
public:
	WindowClose() {};
	static EventType getStaticType() { return EventType::WindowClose; }
	EventType getEventType() const override { return EventType::WindowClose; }
	int getCategoryFlags() const override { return EventCategoryWindow; }
};