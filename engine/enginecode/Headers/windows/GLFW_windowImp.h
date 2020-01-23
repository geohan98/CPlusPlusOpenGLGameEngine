#pragma once

#include "windows/window.h"

struct GLFWwindow;

namespace Engine
{
	/**
	 * GL Vertex Buffer
	 */
	class GLFW_WindowImp : public Window
	{
	private:
		GLFWwindow* m_nativeWindow;  ///< The GLFW window

		void init(const WindowProperties& properties)override; ///< Initialize the window
		void close();  ///<  close the window
		WindowProperties m_properties; ///< window properties
		std::function<void(Events::Event&)> m_callBack; ///< callback to event in application
		float m_aspectRatio; ///< Aspect ratio of the window
	public:
		GLFW_WindowImp(const WindowProperties& proeprties); ///< Constructor
		~GLFW_WindowImp(); ///< Destructor

		void onUpdate(float deltaTime) override; ///< Called Every Frame
		void onResize(unsigned int width, unsigned int height) override; ///< Resize the window
		void setVSync(bool VSync) override; ///< Set Vsync
		void setEventCallback(const std::function<void(Events::Event&)>& callback) override; ///< set Event Callback

		inline unsigned int getWidth() const override { return m_properties.m_width; } ///< Return the window width
		inline unsigned int getHeight() const override { return m_properties.m_height; } ///< Return the Window Height
		inline void* getNativeWindow() const override { return m_nativeWindow; } ///< Return The Native Window
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; } ///< Return if the screen if full screen
		inline bool isVSync() const override { return m_properties.m_isVSync; } ///< Return is Vsync
	};
}