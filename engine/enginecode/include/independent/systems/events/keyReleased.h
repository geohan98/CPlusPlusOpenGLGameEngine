#pragma once

#include "include/independent/systems/events/event.h"

class KeyReleased : public Event
{
private:
	int m_button;
public:
	KeyReleased(int button) : m_button(button) {};
	static EventType getStaticType() { return EventType::KeyReleased; }
	EventType getEventType() const override { return EventType::KeyReleased; }
	int getCategoryFlags() const override { return EventCategoryKeyboard; }

	inline int getButton() const { return m_button; }
};