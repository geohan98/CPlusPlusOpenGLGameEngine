/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "systems/time.h"
#include "include/independent/windows/window.h"
#include "windows/window.h"
#include "windows/windowSystem.h"
#include "systems/events/event.h"
#include "systems/events/applicationEvents.h"
#include "systems/events/keyEvents.h"
#include "systems/ButtonCodes.h"
#include "systems/inputPoller.h"

#include "include/platform/OpenGL/OpenGL_vertexArray.h"
#include "include/platform/OpenGL/OpenGL_vertexBuffer.h"
#include "include/platform/OpenGL/OpenGL_indexBuffer.h"
#include "systems/renderer/bufferLayout.h"
#include "include/platform/OpenGL/OpenGL_texture.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		std::shared_ptr<Window> m_window; //!< Window (abstract)
		static glm::ivec2 s_screenResolution; //!< Screen res
		// Systems
		std::shared_ptr<Log> m_log; //!< Logging system
		std::shared_ptr<Time> m_timer; //!< Timing system
		std::shared_ptr<WindowSystem> m_windows; //!< Windows system
		// shared data
		static float s_timestep; //!< last frame timestep

#pragma region TempVars
// Temp stuff

		std::shared_ptr<OpenGL_VertexArray> vao;
		BufferLayout bl;
		std::shared_ptr<OpenGL_VertexBuffer> vbo;
		std::shared_ptr<OpenGL_IndexBuffer>  ibo;

		std::shared_ptr<OpenGL_VertexArray> vao1;
		BufferLayout bl1;
		std::shared_ptr<OpenGL_VertexBuffer> vbo1;
		std::shared_ptr<OpenGL_IndexBuffer>  ibo1;
		std::shared_ptr<OpenGL_Texture> tex;
		std::shared_ptr<OpenGL_Texture> tex1;

		unsigned int m_FCprogram; // Flat colour shader ID
		unsigned int m_TPprogram; // Textured Phong shader ID
		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?
#pragma endregion TempVars

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline static float getTimestep() { return s_timestep; }
		inline std::shared_ptr<Window> getWindow() { return m_window; }
		void onEvent(Event& e); //!< Called when an event happens
		bool onClose(WindowClose& e); //!< On close event
		bool onResize(WindowResize& e); //!< On resize event
		bool onKeyPressed(KeyPressed& e); //!< On keypress event
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}