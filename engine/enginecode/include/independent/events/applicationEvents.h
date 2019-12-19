#pragma once

#include "event.h"

namespace Engine
{
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

	class WindowClose : public Event
	{
	public:
		WindowClose() {};
		static EventType getStaticType() { return EventType::WindowClose; }
		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

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

	class WindowLostFocus : public Event
	{
	private:
		int m_xPos;
		int m_yPos;
	public:
		WindowLostFocus(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {};
		static EventType getStaticType() { return EventType::WindowLostFocus; }
		EventType getEventType() const override { return EventType::WindowLostFocus; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getxPos() const { return m_xPos; }
		inline int getyPos() const { return m_yPos; }
	};
}