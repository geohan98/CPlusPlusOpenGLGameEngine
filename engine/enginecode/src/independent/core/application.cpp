/** \file application.cpp
*/

#include "engine_pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "include/platform/windows/GLFW_windowSys.h"
#include "include/platform/windows/GLFW_inputPoller.h"
#endif

namespace Engine {

	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 1.0f / 60.0f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);
	glm::mat4 FCmodel, TPmodel;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_log.reset(new Log());
		m_log->start();
		m_timer.reset(new Time());
		m_timer->start();
		m_resources.reset(new ResourceManager());
		m_resources->start();
#ifdef NG_PLATFORM_WINDOWS
		m_windows = std::shared_ptr<WindowSystem>(new GLFW_WindowSys());
		m_inputPoller = std::shared_ptr<InputPoller>(new GLFW_InputPoller());
#endif
		m_windows->start();
		m_window = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		Application::s_screenResolution = glm::ivec2(m_window->getWidth(), m_window->getHeight());

		m_renderer = std::shared_ptr<Renderer>(Renderer::createBasic3D());
		m_renderer->actionCommand(RenderCommand::setBackFaceCullingCommand(true));
		m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(true));

		m_cameraController = std::make_shared<CameraController3D>(CameraController3D());
		m_cameraController->init(60, 800.0f / 600.0f, 0.1, 100);

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


		m_resources->addShader("assets/shaders/flatColor.shader");
		m_resources->addVertexArray("VAO1");
		m_resources->addVertexBuffer("VBO1", FCvertices, sizeof(FCvertices), m_resources->getShader("assets/shaders/flatColor.shader")->getBufferLayout());
		m_resources->addIndexBuffer("Index1", indices, 36);
		m_resources->getVertexArray("VAO1")->setVertexBuffer(m_resources->getVertexBuffer("VBO1"));
		m_resources->getVertexArray("VAO1")->setIndexBuffer(m_resources->getIndexBuffer("Index1"));
		m_resources->addMaterial("FC_CUBE", m_resources->getShader("assets/shaders/flatColor.shader"), m_resources->getVertexArray("VAO1"));
		FCmodel = glm::translate(glm::mat4(1), glm::vec3(0, 0, 3));
	}

	Application::~Application()
	{
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
		if (e.getButton() == KEY_1)
		{
			m_renderer->actionCommand(RenderCommand::setPolygonModeFill());
			return true;
		}
		if (e.getButton() == KEY_2)
		{
			m_renderer->actionCommand(RenderCommand::setPolygonModeLine());
			return true;
		}
		if (e.getButton() == KEY_3)
		{
			m_renderer->actionCommand(RenderCommand::setPolygonModePoint());
			return true;
		}
		return false;
	}

	void Application::run()
	{
		while (m_running)
		{
			m_timer->tick();
			m_timer->reset();
			s_timestep = m_timer->getDeltaTime();
			//LOG_CORE_INFO(1.0f / m_timer->getDeltaTime());

			m_renderer->actionCommand(RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
			m_renderer->actionCommand(RenderCommand::ClearDepthColourBufferCommand());

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);


			FCmodel = glm::rotate(FCmodel, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

			glm::mat4 fcMVP = m_cameraController->getCamera()->getViewProjection() * FCmodel;

			m_resources->getMaterial("FC_CUBE")->setDataElement("u_MVP", &fcMVP[0][0]);
			m_renderer->submit(m_resources->getMaterial("FC_CUBE"));

			glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec3 lightPos = glm::vec3(1.0f, 4.0f, -6.0f);
			glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, -4.5f);

			m_window->onUpdate(s_timestep);
			m_cameraController->onUpdate(s_timestep);
		}
	}

}