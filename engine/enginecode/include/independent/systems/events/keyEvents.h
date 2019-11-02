#pragma once

#include "event.h"

namespace Engine
{
	class KeyPressed : public Event
	{
	public:
		KeyPressed(int button, int repeatCode) {};
		static EventType getStaticType() { return EventType::KeyPressed; }
		EventType getEventType() const override { return EventType::KeyPressed; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }
	};

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
}