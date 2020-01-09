#pragma once

#include "event.h"

namespace Engine
{
	/**
	 *  Window Resize Event
	 */
	class WindowResize : public Event
	{
	private:
		unsigned int m_width;															///< New Window Width
		unsigned int m_height;															///< New Window Height
	public:
		WindowResize(int width, int height) : m_width(width), m_height(height) {};		///< Constructor
		static EventType getStaticType() { return EventType::WindowResize; }			///< Returns the event type
		EventType getEventType() const override { return EventType::WindowResize; }		///< Return the event type
		int getCategoryFlags() const override { return EventCategoryWindow; }			///< Returns the event category

		inline unsigned int getWidth() const { return m_width; }						///< Return the new Window Width
		inline unsigned int getHeight() const { return m_height; }						///< Return the New Window Height
	};
	/**
	 *  Window Close Event
	 */
	class WindowClose : public Event
	{
	public:
		WindowClose() {};																///< Constructor
		static EventType getStaticType() { return EventType::WindowClose; }				///< Returns the event type
		EventType getEventType() const override { return EventType::WindowClose; }		///< Return the event type
		int getCategoryFlags() const override { return EventCategoryWindow; }			///< Returns the event category
	};
	/**
	 *  Window Moved Event
	 */
	class WindowMoved : public Event
	{
	private:
		int m_xPos;																		///< New Window X Position
		int m_yPos;																		///< New Window Y Position
	public:
		WindowMoved(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {};				///< Constructor
		static EventType getStaticType() { return EventType::WindowMoved; }				///< Returns the event type
		EventType getEventType() const override { return EventType::WindowMoved; }		///< Return the event type
		int getCategoryFlags() const override { return EventCategoryWindow; }			///< Returns the event category

		inline int getxPos() const { return m_xPos; }									///< Returns the New Window X Position
		inline int getyPos() const { return m_yPos; }									///< Returns the New Window X Position
	};
	/**
	 *  Window Lost Focus Event
	 */
	class WindowLostFocus : public Event
	{
	private:
		int m_xPos;																		///< New Window X Position
		int m_yPos;																		///< New Window Y Position
	public:
		WindowLostFocus(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {};
		static EventType getStaticType() { return EventType::WindowLostFocus; }			///< Returns the event type
		EventType getEventType() const override { return EventType::WindowLostFocus; }	///< Return the event type
		int getCategoryFlags() const override { return EventCategoryWindow; }			///< Returns the event category

		inline int getxPos() const { return m_xPos; }									///< Returns the New Window X Position
		inline int getyPos() const { return m_yPos; }									///< Returns the New Window X Position
	};
}