#include "engine_pch.h"
#include "systems/log.h"
#include "core/gameLayer.h"
#include "cameras/cameraController3D.h"

namespace Engine
{
	void GameLayer::onAttach()
	{
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


		m_resourceManager = std::shared_ptr<ResourceManager>(new ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer>(Renderer::createBasic3D());
		m_renderer->actionCommand(RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);

		m_resourceManager->addShader("assets/shaders/flatColor.shader");
		m_resourceManager->addVertexArray("VAO1");
		m_resourceManager->addVertexBuffer("VBO1", FCvertices, sizeof(FCvertices), m_resourceManager->getShader("assets/shaders/flatColor.shader")->getBufferLayout());
		m_resourceManager->addIndexBuffer("Index1", indices, 36);
		m_resourceManager->getVertexArray("VAO1")->setVertexBuffer(m_resourceManager->getVertexBuffer("VBO1"));
		m_resourceManager->getVertexArray("VAO1")->setIndexBuffer(m_resourceManager->getIndexBuffer("Index1"));
		m_resourceManager->addMaterial("FC_CUBE", m_resourceManager->getShader("assets/shaders/flatColor.shader"), m_resourceManager->getVertexArray("VAO1"));

		m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(m_resourceManager->getMaterial("FC_CUBE"))));
		m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
		m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 45.0f, 0.0f))));


		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject()));
		m_gameObjects.back()->addComponent(m_materials.back());
		m_gameObjects.back()->addComponent(m_positions.back());
		m_gameObjects.back()->addComponent(m_velocities.back());
	}

	void GameLayer::onDetach()
	{

	}

	void GameLayer::onUpdate(float timestep)
	{
		m_camera->onUpdate(timestep);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(timestep);
		}

		m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(RenderCommand::setBackFaceCullingCommand(true));
		m_renderer->actionCommand(RenderCommand::ClearDepthColourBufferCommand());

		for (auto& mat : m_materials)
		{
			std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			mat->receiveMessage(msg);
			m_renderer->submit(mat->getMaterial());
		}

		m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(false));
		m_renderer->actionCommand(RenderCommand::setBackFaceCullingCommand(false));
	}

	void GameLayer::onEvent(Event& e)
	{
		m_camera->onEvent(e);
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowResize>(std::bind(&GameLayer::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowClose>(std::bind(&GameLayer::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMoved>(std::bind(&GameLayer::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&GameLayer::onWindowLostFocus, this, std::placeholders::_1));

		dispatcher.dispatch<KeyPressed>(std::bind(&GameLayer::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleased>(std::bind(&GameLayer::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<KeyTyped>(std::bind(&GameLayer::onKeyTyped, this, std::placeholders::_1));

		dispatcher.dispatch<MouseMoved>(std::bind(&GameLayer::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolled>(std::bind(&GameLayer::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&GameLayer::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&GameLayer::onMouseButtonReleased, this, std::placeholders::_1));
	}


	bool GameLayer::onWindowResize(WindowResize& e)
	{
		return true;
	}

	bool GameLayer::onWindowClose(WindowClose& e)
	{
		return true;
	}

	bool GameLayer::onWindowMoved(WindowMoved& e)
	{
		return true;
	}

	bool GameLayer::onWindowLostFocus(WindowLostFocus& e)
	{
		return true;
	}

	bool GameLayer::onKeyPressed(KeyPressed& e)
	{
		if (e.getButton() == KEY_1)
		{
			m_renderer->actionCommand(RenderCommand::setPolygonModeFill());
		}
		if (e.getButton() == KEY_2)
		{
			m_renderer->actionCommand(RenderCommand::setPolygonModeLine());
		}
		if (e.getButton() == KEY_3)
		{
			m_renderer->actionCommand(RenderCommand::setPolygonModePoint());
		}
		return true;
	}

	bool GameLayer::onKeyReleased(KeyReleased& e)
	{
		return true;
	}

	bool GameLayer::onKeyTyped(KeyTyped& e)
	{
		return true;
	}

	bool GameLayer::onMouseMove(MouseMoved& e)
	{
		return true;
	}

	bool GameLayer::onMouseScrolled(MouseScrolled& e)
	{
		return true;
	}

	bool GameLayer::onMouseButtonPressed(MouseButtonPressed& e)
	{
		return true;
	}

	bool GameLayer::onMouseButtonReleased(MouseButtonReleased& e)
	{
		return true;
	}
}