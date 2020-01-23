#pragma once

#include "event.h"

namespace Engine
{

	namespace Events {

		/**
		 *  Key Pressed Event
		 */
		class KeyPressed : public Event
		{
		private:
			int m_button; ///< Button Code
			int m_repeatCount; ///< Button Held For X Frames
		public:
			KeyPressed(int button, int repeatCode) : m_button(button), m_repeatCount(repeatCode) {}; ///< Constructor
			static EventType getStaticType() { return EventType::KeyPressed; }			///< Return Event Type
			EventType getEventType() const override { return EventType::KeyPressed; }	///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryKeyboard; }		///< Return Event Category

			inline int getButton() const { return m_button; } ///< Return Button Code
			inline int getRepeatCount() const { return m_repeatCount; } ///< Return the Repeat Count
		};
		/**
		 *  Key Released Event
		 */
		class KeyReleased : public Event
		{
		private:
			int m_button; ///< Button Code
		public:
			KeyReleased(int button) : m_button(button) {};
			static EventType getStaticType() { return EventType::KeyReleased; }			///< Return Event Type
			EventType getEventType() const override { return EventType::KeyReleased; }	///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryKeyboard; }		///< Return Event Category

			inline int getButton() const { return m_button; } ///< Return Button Code
		};
		/**
		 *  Key Typed Event
		 */
		class KeyTyped : public Event
		{
		private:
			int m_button; ///< Button Code
		public:
			KeyTyped(int button) : m_button(button) {};
			static EventType getStaticType() { return EventType::KeyTyped; }		///< Return Event Type
			EventType getEventType() const override { return EventType::KeyTyped; }	///< Return Event Type
			int getCategoryFlags() const override { return EventCategoryKeyboard; }	///< Return Event Category

			inline int getButton() const { return m_button; } ///< Return Button Code
		};
	}
}