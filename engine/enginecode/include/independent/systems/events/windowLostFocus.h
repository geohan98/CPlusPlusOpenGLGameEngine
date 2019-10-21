#pragma once

#include "include/independent/systems/events/event.h"

class WindowLostFocus : Event
{
private:
	int m_xPos;
	int m_yPos;
public:
	WindowLostFocus(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {};
	EventType getEventType() const override { return EventType::WindowLostFocus; }
	int getCategoryFlags() const override { return EventCategoryWindow; }

	inline int getxPos() const { return m_xPos; }
	inline int getyPos() const { return m_yPos; }
};