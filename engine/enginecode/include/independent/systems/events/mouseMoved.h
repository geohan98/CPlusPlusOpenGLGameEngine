#pragma once

#include "include/independent/systems/events/event.h"

class MouseMoved : public Event
{
private:
	int m_xPos;
	int m_yPos;
public:
	MouseMoved(float xPos, float yPos) : m_xPos(xPos), m_yPos(yPos) {};
	static EventType getStaticType() { return EventType::MouseMoved; }
	EventType getEventType() const override { return EventType::MouseMoved; }
	int getCategoryFlags() const override { return EventCategoryMouse; }

	inline int getxPos() const { return m_xPos; }
	inline int getyPos() const { return m_yPos; }
};