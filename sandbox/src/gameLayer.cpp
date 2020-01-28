#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "gameLayer.h"
#include "../enginecode/Headers/cameras/cameraController3D.h"
#include "../enginecode/Headers/fileLoaders/textLoader.h"
#include "../enginecode/Headers/fileLoaders/JSONLoaderLog.h"

#include "../imgui/imgui.h"

namespace Engine
{
	void GameLayer::onAttach()
	{
		TextModel mesh;
		std::string filepath = "assets/models/fccube.txt";
		TextLoader::loadModel(m_resourceManager, filepath, mesh);

		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
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


		Renderer::UniformBufferLayout layout = { Renderer::ShaderDataType::Mat4,Renderer::ShaderDataType::Mat4 };
		m_uniformBuffer = std::shared_ptr<Renderer::UniformBuffer>(Renderer::UniformBuffer::create(2 * sizeof(glm::mat4), layout));

		m_uniformBuffer->attachShaderBlock(m_resourceManager->getMaterial("FC_CUBE")->getShader(), "Matrices");
		std::vector<void*> sceneData(2);
		sceneData[0] = (void*)&m_camera->getCamera()->getProjection();
		sceneData[1] = (void*)&m_camera->getCamera()->getView();
		m_sceneData[m_uniformBuffer] = sceneData;

	}

	void GameLayer::onDetach()
	{

	}

	void GameLayer::onUpdate(float deltaTime)
	{
		m_renderer->beginScene(m_sceneData);

		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::ClearDepthColourBufferCommand());

		for (auto& mat : m_materials)
		{
			/*std::pair<std::string, void*> data("u_vp", (void*)& m_camera->getCamera()->getViewProjection()[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			mat->receiveMessage(msg);*/
			m_renderer->submit(mat->getMaterial());
		}
	}

	void GameLayer::onEvent(Events::Event& e)
	{
		//Send Event to Camera Controller
		m_camera->onEvent(e);
		//Send Event to All Game Objects
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);

		//Dispatch Event to Game Layer
		Events::EventDispatcher dispatcher(e);
		//Application Events
		dispatcher.dispatch<Events::WindowResize>(std::bind(&GameLayer::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowClose>(std::bind(&GameLayer::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowMoved>(std::bind(&GameLayer::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowLostFocus>(std::bind(&GameLayer::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispatcher.dispatch<Events::KeyPressed>(std::bind(&GameLayer::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyReleased>(std::bind(&GameLayer::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyTyped>(std::bind(&GameLayer::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispatcher.dispatch<Events::MouseMoved>(std::bind(&GameLayer::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseScrolled>(std::bind(&GameLayer::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseButtonPressed>(std::bind(&GameLayer::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseButtonReleased>(std::bind(&GameLayer::onMouseButtonReleased, this, std::placeholders::_1));
	}

	bool GameLayer::onWindowResize(Events::WindowResize& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: CLOSING APPLICATION");
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onWindowMoved(Events::WindowMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onWindowLostFocus(Events::WindowLostFocus& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onKeyPressed(Events::KeyPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: KEY PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onKeyReleased(Events::KeyReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: KEY RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG
		if (e.getButton() == KEY_R)
		{
#ifdef NG_DEBUG
			LOG_CORE_INFO("GAME LAYER: RESET CAMERA");
#endif // NG_DEBUG
			m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);
		}
		return true;
	}

	bool GameLayer::onKeyTyped(Events::KeyTyped& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: KEY TYPED '{0}'", e.getButton());
#endif // NG_DEBUG

		return true;
	}

	bool GameLayer::onMouseMove(Events::MouseMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onMouseScrolled(Events::MouseScrolled& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onMouseButtonPressed(Events::MouseButtonPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: MOUSE BUTTON PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool GameLayer::onMouseButtonReleased(Events::MouseButtonReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("GAME LAYER: MOUSE BUTTON RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}
}