#pragma once

#include "include/independent/systems/events/event.h"

class WindowResize : public Event
{
private:
	unsigned int m_width;
	unsigned int m_height;
public:
	WindowResize(int width, int height) : m_width(width), m_height(height) {};
	static EventType getStaticType() { return EventType::WindowResize; }
	EventType getEventType() const override { return EventType::WindowResize; }
	int getCategoryFlags() const override { return EventCategoryWindow; }

	inline unsigned int getWidth() const { return m_width; }
	inline unsigned int getHeight() const { return m_height; }
};