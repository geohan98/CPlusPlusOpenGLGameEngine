#pragma once

#include "include/independent/systems/events/event.h"

class KeyTyped : public Event
{
private:
	int m_button;
public:
	KeyTyped(int button) : m_button(button) {};
	static EventType getStaticType() { return EventType::KeyTyped; }
	EventType getEventType() const override { return EventType::KeyTyped; }
	int getCategoryFlags() const override { return EventCategoryKeyboard; }

	inline int getButton() const { return m_button; }
};