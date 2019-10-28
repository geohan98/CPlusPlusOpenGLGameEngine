#pragma once

#include "include/independent/systems/events/event.h"

class WindowMoved : public Event
{
private: 
	int m_xPos;
	int m_yPos;
public:
	WindowMoved(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {};
	static EventType getStaticType() { return EventType::WindowMoved; }
	EventType getEventType() const override { return EventType::WindowMoved; }
	int getCategoryFlags() const override { return EventCategoryWindow; }

	inline int getxPos() const { return m_xPos; }
	inline int getyPos() const { return m_yPos; }
};