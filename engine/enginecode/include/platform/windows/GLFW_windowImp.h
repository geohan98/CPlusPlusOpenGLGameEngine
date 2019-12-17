#pragma once

#include "windows/window.h"

struct GLFWwindow;

namespace Engine
{
	class GLFW_WindowImp : public Window
	{
	private:
		GLFWwindow* m_nativeWindow;

		void init(const WindowProperties& properties)override;
		void close();
		WindowProperties m_properties;
		std::function<void(Event&)> m_callBack;
		float m_aspectRatio;
	public:
		GLFW_WindowImp(const WindowProperties& proeprties);
		~GLFW_WindowImp();

		void onUpdate(float timestep) override;
		void onResize(unsigned int width, unsigned int height) override;
		void setVSync(bool VSync) override;
		void setEventCallback(const std::function<void(Event&)>& callback) override;

		inline unsigned int getWidth() const override { return m_properties.m_width; }
		inline unsigned int getHeight() const override { return m_properties.m_height; }
		inline void* getNativeWindow() const override { return m_nativeWindow; }
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; }
		inline bool isVSync() const override { return m_properties.m_isVSync; }
	};
}