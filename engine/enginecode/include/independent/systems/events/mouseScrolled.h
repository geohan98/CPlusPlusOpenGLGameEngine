#pragma once

#include "include/independent/systems/events/event.h"

class MouseScrolled : Event
{
private:
	int m_xDelta;
	int m_yDelta;
public:
	MouseScrolled(float xDelta, float yDelta) : m_xDelta(xDelta), m_yDelta(yDelta) {};
	EventType getEventType() const override { return EventType::MouseScrolled; }
	int getCategoryFlags() const override { return EventCategoryMouse; }

	inline int getxDelta() const { return m_xDelta; }
	inline int getyDelta() const { return m_yDelta; }
};