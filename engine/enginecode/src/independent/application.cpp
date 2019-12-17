/** \file application.cpp
*/

#include "engine_pch.h"

#pragma region TempIncludes
// temp includes
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma endregion TempIncludes

#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "include/platform/windows/GLFW_windowSys.h"

#endif // NG_PLATFORM_WINDOWS

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 1.0f / 60.0f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);

#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems 
		m_log.reset(new Log());
		m_log->start();
		m_timer.reset(new Time());
		m_timer->start();
#ifdef NG_PLATFORM_WINDOWS
		m_windows = std::shared_ptr<WindowSystem>(new GLFW_WindowSys());
#endif // NG_PLATFORM_WINDOWS
		m_windows->start();
		LOG_CORE_WARN("WINDOW SYSTEM INITALISED");

		// Create window
		m_window = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		// Set screen res
		Application::s_screenResolution = glm::ivec2(m_window->getWidth(), m_window->getHeight());

		m_resources.reset(new ResourceManager());

#pragma region TempSetup
		//  Temporary set up code to be abstracted

		// Enable standard depth detest (Z-buffer)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};

		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};


		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

		tex = std::shared_ptr<OpenGL_Texture>(new OpenGL_Texture("assets/textures/letterCube.png"));
		tex->bind();
		tex1 = std::shared_ptr<OpenGL_Texture>(new OpenGL_Texture("assets/textures/numberCube.png"));
		tex1->bind();

		prog = std::shared_ptr<OpenGL_Shader>(new OpenGL_Shader("assets/shaders/flatColor.shader"));

		prog1 = std::shared_ptr<OpenGL_Shader>(new OpenGL_Shader("assets/shaders/texPhong.shader"));

		bl = { {ShaderDataType::Float3},{ShaderDataType::Float3} };
		vao = std::shared_ptr<OpenGL_VertexArray>(new OpenGL_VertexArray());
		vbo = std::shared_ptr<OpenGL_VertexBuffer>(new OpenGL_VertexBuffer(FCvertices, sizeof(FCvertices), prog->getBufferLayout()));
		vbo->bind();
		ibo = std::shared_ptr<OpenGL_IndexBuffer>(new OpenGL_IndexBuffer(indices, 36));
		ibo->bind();
		vao->setVertexBuffer(vbo);
		vao->setIndexBuffer(ibo);
		vao->bind();


		bl1 = { {ShaderDataType::Float3},{ShaderDataType::Float3},{ShaderDataType::Float2} };
		vao1 = std::shared_ptr<OpenGL_VertexArray>(new OpenGL_VertexArray());
		vbo1 = std::shared_ptr<OpenGL_VertexBuffer>(new OpenGL_VertexBuffer(TPvertices, sizeof(TPvertices), prog1->getBufferLayout()));
		vbo1->bind();
		ibo1 = std::shared_ptr<OpenGL_IndexBuffer>(new OpenGL_IndexBuffer(indices, 36));
		ibo1->bind();
		vao1->setVertexBuffer(vbo1);
		vao1->setIndexBuffer(ibo);
		vao1->bind();




#pragma endregion TempSetup

		// Reset timer
		m_timer->getDeltaTime();
	}

	Application::~Application()
	{
		// Stop systems
		m_timer->stop();
		m_log->stop();
	}

	void Application::onEvent(Event& e)
	{
		LOG_CORE_INFO("EVENT: {0}", e.getEventType());

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResize>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
	}

	bool Application::onClose(WindowClose& e)
	{
		LOG_CORE_WARN("CLOSING APPLICATION");
		m_running = false;
		return true;
	}

	bool Application::onResize(WindowResize& e)
	{
		m_window->onResize(e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onKeyPressed(KeyPressed& e)
	{
		if (e.getButton() == KEY_ESCAPE) //Escape
		{
			m_running = false;
			return true;
		}
		if (e.getButton() == KEY_TAB)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			return true;
		}
		return false;
	}

	void Application::run()
	{

		LOG_CORE_INFO(m_resources->parseFilePath("assets/textures/letterCube.png"));

		while (m_running)
		{

#pragma region TempDrawCode
			// Temporary draw code to be abstracted

			glClearColor(0.8f, 0.8f, 0.8f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move, you can ignore this more or less.
			glm::mat4 FCtranslation, TPtranslation;

			if (m_goingUp)
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
			}
			else
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
			}

			m_timeSummed += s_timestep;
			if (m_timeSummed > 20.0f) {
				m_timeSummed = 0.f;
				m_goingUp = !m_goingUp;
			}


			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

			// End of code to make the cube move.

			glm::mat4 fcMVP = projection * view * FCmodel;

			prog->bind();
			prog->uploadData("u_MVP", &fcMVP[0][0]);
			vao->bind();

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); //DRAW CALL

			glm::mat4 tpMVP = projection * view * TPmodel;
			unsigned int texSlot;
			if (m_goingUp) texSlot = 0;
			else texSlot = 1;

			glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec3 lightPos = glm::vec3(1.0f, 4.0f, -6.0f);
			glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, -4.5f);

			prog1->bind();
			prog1->uploadData("u_MVP", (void*)&tpMVP[0][0]);
			prog1->uploadData("u_model", (void*)&TPmodel[0][0]);
			prog1->uploadData("u_lightColour", (void*)&lightColour);
			prog1->uploadData("u_lightPos", (void*)&lightPos);
			prog1->uploadData("u_viewPos", (void*)&viewPos);
			prog1->uploadData("u_texData", (void*)&texSlot);


			vao1->bind();
			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr); //DRAW CALL

			// End temporary code
#pragma endregion TempDrawCode

			m_window->onUpdate(s_timestep);

		}
	}

}