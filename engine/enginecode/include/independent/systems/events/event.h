#pragma once

#include "engine_pch.h"

namespace Engine {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,		//00000001
		EventCategoryInput = 1 << 1,		//00000010
		EventCategoryKeyboard = 1 << 2,		//00000100
		EventCategoryMouse = 1 << 3,		//00001000
		EventCategoryMouseButton = 1 << 4	//00010000
	};

	class Event {
	private:
		bool m_handled = false;
	public:
		virtual EventType getEventType() const = 0;
		virtual int getCategoryFlags() const = 0;
		inline bool handled() const { return m_handled; }
		inline void handle(bool isHandled) { m_handled = isHandled; }
		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_event(event) {}

		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));

				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

}