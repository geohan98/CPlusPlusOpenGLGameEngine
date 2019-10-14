#pragma once

#include "include/independent/systems/events/event.h"

class MouseMoved : Event
{
private:
	int m_xPos;
	int m_yPos;
public:
	MouseMoved(float xPos, float yPos) : m_xPos(xPos), m_yPos(yPos) {};
	EventType getEventType() const override { return EventType::MouseMoved; }
	int getCategoryFlags() const override { return EventCategoryMouse; }

	inline int getxPos() const { return m_xPos; }
	inline int getyPos() const { return m_yPos; }
};