#pragma once

#include "include/independent/systems/events/event.h"

class MouseButtonPressed : Event
{
private:
	int m_button;
public:
	MouseButtonPressed(int button) : m_button(button) {};
	EventType getEventType() const override { return EventType::MouseButtonPressed; }
	int getCategoryFlags() const override { return EventCategoryMouseButton; }

	inline int getButton() const { return m_button; }
};