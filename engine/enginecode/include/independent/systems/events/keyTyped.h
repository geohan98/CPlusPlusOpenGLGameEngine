#pragma once

#include "include/independent/systems/events/event.h"

class KeyTyped : Event
{
private:
	int m_button;
public:
	KeyTyped(int button) : m_button(button) {};
	EventType getEventType() const override { return EventType::KeyTyped; }
	int getCategoryFlags() const override { return EventCategoryKeyboard; }

	inline int getButton() const { return m_button; }
};