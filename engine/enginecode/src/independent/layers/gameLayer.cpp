#include "engine_pch.h"
#include "systems/log.h"
#include "layers/gameLayer.h"
#include "cameras/cameraController3D.h"
#include "fileLoaders/textLoader.h"
#include "fileLoaders/JSONLoaderLog.h"

namespace Engine
{
	void GameLayer::onAttach()
	{
		TextModel mesh;
		std::string filepath = "assets/models/fccube.txt";
		TextLoader::loadModel(m_resourceManager, filepath, mesh);

		m_resourceManager = std::shared_ptr<ResourceManager>(new ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer>(Renderer::createBasic3D());
		m_renderer->actionCommand(RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);

		m_resourceManager->addVertexArray("VAO1");
		m_resourceManager->addVertexBuffer("VBO1", mesh.vertices, mesh.verticesSize, mesh.shader->getBufferLayout());
		m_resourceManager->addIndexBuffer("Index1", mesh.indices, mesh.indicesSize);
		m_resourceManager->getVertexArray("VAO1")->setVertexBuffer(m_resourceManager->getVertexBuffer("VBO1"));
		m_resourceManager->getVertexArray("VAO1")->setIndexBuffer(m_resourceManager->getIndexBuffer("Index1"));
		m_resourceManager->addMaterial("FC_CUBE", mesh.shader, m_resourceManager->getVertexArray("VAO1"));

		m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(m_resourceManager->getMaterial("FC_CUBE"))));
		m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
		m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 45.0f, 0.0f))));


		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject()));
		m_gameObjects.back()->addComponent(m_materials.back());
		m_gameObjects.back()->addComponent(m_positions.back());
		m_gameObjects.back()->addComponent(m_velocities.back());


		JSONLoaderLog::load("assets/levels/cubeLevel.json");

	}

	void GameLayer::onDetach()
	{

	}

	void GameLayer::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
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


	}

	void GameLayer::onEvent(Event& e)
	{
		//Send Event to Camera Controller
		m_camera->onEvent(e);
		//Send Event to All Game Objects
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);

		//Dispatch Event to Game Layer
		EventDispatcher dispatcher(e);
		//Application Events
		dispatcher.dispatch<WindowResize>(std::bind(&GameLayer::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowClose>(std::bind(&GameLayer::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMoved>(std::bind(&GameLayer::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&GameLayer::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispatcher.dispatch<KeyPressed>(std::bind(&GameLayer::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleased>(std::bind(&GameLayer::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<KeyTyped>(std::bind(&GameLayer::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispatcher.dispatch<MouseMoved>(std::bind(&GameLayer::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolled>(std::bind(&GameLayer::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&GameLayer::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&GameLayer::onMouseButtonReleased, this, std::placeholders::_1));
	}


	bool GameLayer::onWindowResize(WindowResize& e)
	{
		LOG_CORE_INFO("GAME LAYER: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
		return true;
	}

	bool GameLayer::onWindowClose(WindowClose& e)
	{
		LOG_CORE_INFO("GAME LAYER: CLOSING APPLICATION");
		return true;
	}

	bool GameLayer::onWindowMoved(WindowMoved& e)
	{
		LOG_CORE_INFO("GAME LAYER: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
		return true;
	}

	bool GameLayer::onWindowLostFocus(WindowLostFocus& e)
	{
		LOG_CORE_INFO("GAME LAYER: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
		return true;
	}

	bool GameLayer::onKeyPressed(KeyPressed& e)
	{
		LOG_CORE_INFO("GAME LAYER: KEY PRESSED '{0}'", e.getButton());
		return true;
	}

	bool GameLayer::onKeyReleased(KeyReleased& e)
	{
		LOG_CORE_INFO("GAME LAYER: KEY RELEASED '{0}'", e.getButton());
		if (e.getButton() == KEY_R)
		{
			LOG_CORE_INFO("GAME LAYER: RESET CAMERA");
			m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);
		}
		return true;
	}

	bool GameLayer::onKeyTyped(KeyTyped& e)
	{
		LOG_CORE_INFO("GAME LAYER: KEY TYPED '{0}'", e.getButton());
		return true;
	}

	bool GameLayer::onMouseMove(MouseMoved& e)
	{
		LOG_CORE_INFO("GAME LAYER: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
		return true;
	}

	bool GameLayer::onMouseScrolled(MouseScrolled& e)
	{
		LOG_CORE_INFO("GAME LAYER: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());
		return true;
	}

	bool GameLayer::onMouseButtonPressed(MouseButtonPressed& e)
	{
		LOG_CORE_INFO("GAME LAYER: MOUSE BUTTON PRESSED '{0}'", e.getButton());
		return true;
	}

	bool GameLayer::onMouseButtonReleased(MouseButtonReleased& e)
	{
		LOG_CORE_INFO("GAME LAYER: MOUSE BUTTON RELEASED '{0}'", e.getButton());
		return true;
	}
}