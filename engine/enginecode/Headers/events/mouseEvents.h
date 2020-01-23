#pragma once

#include "event.h"

namespace Engine
{

	namespace Events {
		/**
		 *  Mouse Move EBent
		 */
		class MouseMoved : public Event
		{
		private:
			int m_xPos; ///< Mouse New X Position
			int m_yPos;	///< Mouse New Y Position
		public:
			MouseMoved(float xPos, float yPos) : m_xPos(xPos), m_yPos(yPos) {};			///< Constructor
			static EventType getStaticType() { return EventType::MouseMoved; }			///< Return Event Type
			EventType getEventType() const override { return EventType::MouseMoved; }	///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryMouse; }		///< Return Event Category

			inline int getxPos() const { return m_xPos; } ///< Return new Mouse New X Position
			inline int getyPos() const { return m_yPos; } ///< Return new Mouse New Y Position
		};
		/**
		 *  Mouse Scroll Event
		 */
		class MouseScrolled : public Event
		{
		private:
			int m_xDelta; ///< Scroll X Delta
			int m_yDelta; ///< Scroll Y Delta
		public:
			MouseScrolled(float xDelta, float yDelta) : m_xDelta(xDelta), m_yDelta(yDelta) {};	///< Constructor
			static EventType getStaticType() { return EventType::MouseScrolled; }				///< Return Event Type
			EventType getEventType() const override { return EventType::MouseScrolled; }		///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryMouse; }				///< Return Event Category

			inline int getxDelta() const { return m_xDelta; } ///< Return Scroll  X Direction
			inline int getyDelta() const { return m_yDelta; } ///< Return Scroll  Y Direction
		};
		/**
		 *  Mouse Event
		 */
		class MouseButtonPressed : public Event
		{
		private:
			int m_button; ///< Button Code
		public:
			MouseButtonPressed(int button) : m_button(button) {};								///< Constructor
			static EventType getStaticType() { return EventType::MouseButtonPressed; }			///< Return Event Type
			EventType getEventType() const override { return EventType::MouseButtonPressed; }	///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryMouseButton; }			///< Return Event Category

			inline int getButton() const { return m_button; } ///< Return Button Code
		};
		/**
		 *  Mouse Event
		 */
		class MouseButtonReleased : public Event
		{
		private:
			int m_button; ///< Button Code
		public:
			MouseButtonReleased(int button) : m_button(button) {};								///< Constructor
			static EventType getStaticType() { return EventType::MouseButtonReleased; }			///< Return Event Type
			EventType getEventType() const override { return EventType::MouseButtonReleased; }	///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryMouseButton; }			///< Return Event Category

			inline int getButton() const { return m_button; } ///< Return Button Code
		};
	}
}