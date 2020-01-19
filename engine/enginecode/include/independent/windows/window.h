#pragma once
#include "graphicsContext.h"
#include <string>
#include <functional>
#include "events/event.h"
#include "events/applicationEvents.h"
#include "events/mouseEvents.h"
#include "events/keyEvents.h"

namespace Engine {

	/**
	 * Struct to hold properties about windows
	 */
	struct WindowProperties
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_isFullScreen;
		bool m_isVSync;

		WindowProperties(const std::string& title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen) {}
	};

	/**
	 * Window, holds information about a window
	 */
	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0;						///< Init the window with properties
		virtual void close() = 0;														///< close the window
		virtual ~Window() {};															///< destructor
		virtual void onUpdate(float deltaTime) = 0;										///< runs every frame
		virtual void onResize(unsigned int width, unsigned int height) = 0;				///< on resize event
		virtual void setVSync(bool VSync) = 0;											///< set is vsync
		virtual void setEventCallback(const std::function<void(Events::Event&)>& callback) = 0;	///< set the event callback function
		virtual unsigned int getWidth() const = 0;										///< return the window width
		virtual unsigned int getHeight() const = 0;										///< return window height
		virtual void* getNativeWindow() const = 0;										///< get the native window
		virtual bool isFullScreenMode() const = 0;										///< return is fullscreen
		virtual bool isVSync() const = 0;												///< return is vsync

		static Window* create(const WindowProperties& properties = WindowProperties());	///< Creates API specific window
	protected:
		std::unique_ptr<GraphicsContext> m_context;										///<  pointer to graphics context
	};
}

