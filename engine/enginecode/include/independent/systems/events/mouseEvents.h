

#include "event.h"

namespace Engine
{
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

	class MouseScrolled : public Event
	{
	private:
		int m_xDelta;
		int m_yDelta;
	public:
		MouseScrolled(float xDelta, float yDelta) : m_xDelta(xDelta), m_yDelta(yDelta) {};
		static EventType getStaticType() { return EventType::MouseScrolled; }
		EventType getEventType() const override { return EventType::MouseScrolled; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getxDelta() const { return m_xDelta; }
		inline int getyDelta() const { return m_yDelta; }
	};

	class MouseButtonPressed : public Event
	{
	private:
		int m_button;
	public:
		MouseButtonPressed(int button) : m_button(button) {};
		static EventType getStaticType() { return EventType::MouseButtonPressed; }
		EventType getEventType() const override { return EventType::MouseButtonPressed; }
		int getCategoryFlags() const override { return EventCategoryMouseButton; }

		inline int getButton() const { return m_button; }
	};

	class MouseButtonReleased : public Event
	{
	private:
		int m_button;
	public:
		MouseButtonReleased(int button) : m_button(button) {};
		static EventType getStaticType() { return EventType::MouseButtonReleased; }
		EventType getEventType() const override { return EventType::MouseButtonReleased; }
		int getCategoryFlags() const override { return EventCategoryMouseButton; }

		inline int getButton() const { return m_button; }
	};
}