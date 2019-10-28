#pragma once

#include "include/independent/systems/events/event.h"

class MouseButtonReleased : public Event
{
private:
	int m_button;
public:
	MouseButtonReleased(int button) : m_button(button) {};
	static EventType getStaticType() { return EventType::MouseButtonReleased; }
	EventType getEventType() const override { return EventType::MouseButtonReleased; }
	int getCategoryFlags() const override { return EventCategoryMouseButton; }

	inline int getButton() const { return m_button; }
};