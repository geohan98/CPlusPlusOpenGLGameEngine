#pragma once

#include "systems/events/event.h"


class EventDispatcher
{
	template<typename T>
	using EventFunc = std::function<bool(t&)>;
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