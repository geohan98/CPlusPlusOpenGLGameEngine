#include "engine_pch.h"
#include "systems/log.h"
#include "layers/layer2D.h"
#include "cameras/cameraController2D.h"
#include "fileLoaders/textLoader.h"

namespace Engine
{

	void Layer2D::onAttach()
	{
		m_resourceManager = std::shared_ptr<ResourceManager>(new ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer>(Renderer::createBasic2D());
		m_renderer->actionCommand(RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
		m_renderer->actionCommand(RenderCommand::setBlendMode(true));
		m_camera = std::shared_ptr<CameraController2D>(new CameraController2D);
		m_camera->init(0.0f, 800.0f, 600.0f, 0.0f);


		float verts[4 * 4] =
		{
			-75.0f, -75.0f, 0.0f, 1.0f,
			-75.0f, 75.0f, 0.0f, 0.0f,
			75.0f, 75.0f, 1.0f, 0.0f,
			75.0f, -75.0f, 1.0f, 1.0f
		};

		unsigned int indices[4] = { 0,1,2,3 };

		m_resourceManager->addShader("assets/shaders/2DQuad.shader");
		m_resourceManager->addVertexArray("TEXT");
		m_resourceManager->addVertexBuffer("TEXT", verts, sizeof(verts), m_resourceManager->getShader("assets/shaders/2DQuad.shader")->getBufferLayout());
		m_resourceManager->addIndexBuffer("TEXT", indices, 4);
		m_resourceManager->getVertexArray("TEXT")->setVertexBuffer(m_resourceManager->getVertexBuffer("TEXT"));
		m_resourceManager->getVertexArray("TEXT")->setIndexBuffer(m_resourceManager->getIndexBuffer("TEXT"));
		m_resourceManager->addTexture("assets/textures/face.png");
		m_resourceManager->addMaterial("TEXT", m_resourceManager->getShader("assets/shaders/2DQuad.shader"), m_resourceManager->getVertexArray("TEXT"));

		m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(m_resourceManager->getMaterial("TEXT"))));
		m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(400.0f, 75.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
		m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f))));
		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
		m_gameObjects.back()->addComponent(m_materials.back());
		m_gameObjects.back()->addComponent(m_positions.back());
		m_gameObjects.back()->addComponent(m_velocities.back());
	}

	void Layer2D::onDetach()
	{

	}

	void Layer2D::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(false));
		m_renderer->actionCommand(RenderCommand::setBackFaceCullingCommand(false));

		std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
		ComponentMessage msg(ComponentMessageType::UniformSet, data);
		m_materials.back()->receiveMessage(msg);

		unsigned int texSlot = 0;
		m_materials.back()->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
		glm::mat4 model = glm::mat4(1.0f);
		//m_materials.back()->getMaterial()->setDataElement("u_model", (void*)&model[0][0]);
		m_resourceManager->getTexture("assets/textures/face.png")->bind();

		m_renderer->submit(m_materials.back()->getMaterial());
	}

	void Layer2D::onEvent(Event& e)
	{
		m_camera->onEvent(e);

		//Dispatch Event to Game Layer
		EventDispatcher dispatcher(e);
		//Application Events
		dispatcher.dispatch<WindowResize>(std::bind(&Layer2D::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowClose>(std::bind(&Layer2D::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMoved>(std::bind(&Layer2D::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&Layer2D::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispatcher.dispatch<KeyPressed>(std::bind(&Layer2D::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleased>(std::bind(&Layer2D::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<KeyTyped>(std::bind(&Layer2D::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispatcher.dispatch<MouseMoved>(std::bind(&Layer2D::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolled>(std::bind(&Layer2D::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&Layer2D::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&Layer2D::onMouseButtonReleased, this, std::placeholders::_1));
	}

	bool Layer2D::onWindowResize(WindowResize& e)
	{
		LOG_CORE_INFO("LAYER 2D: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
		return true;
	}

	bool Layer2D::onWindowClose(WindowClose& e)
	{
		LOG_CORE_INFO("LAYER 2D: CLOSING APPLICATION");
		return true;
	}

	bool Layer2D::onWindowMoved(WindowMoved& e)
	{
		LOG_CORE_INFO("LAYER 2D: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
		return true;
	}

	bool Layer2D::onWindowLostFocus(WindowLostFocus& e)
	{
		LOG_CORE_INFO("LAYER 2D: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
		return true;
	}

	bool Layer2D::onKeyPressed(KeyPressed& e)
	{
		LOG_CORE_INFO("LAYER 2D: KEY PRESSED '{0}'", e.getButton());
		return true;
	}

	bool Layer2D::onKeyReleased(KeyReleased& e)
	{
		LOG_CORE_INFO("LAYER 2D: KEY RELEASED '{0}'", e.getButton());
		return true;
	}

	bool Layer2D::onKeyTyped(KeyTyped& e)
	{
		LOG_CORE_INFO("LAYER 2D: KEY TYPED '{0}'", e.getButton());
		return true;
	}

	bool Layer2D::onMouseMove(MouseMoved& e)
	{
		LOG_CORE_INFO("LAYER 2D: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
		return true;
	}

	bool Layer2D::onMouseScrolled(MouseScrolled& e)
	{
		LOG_CORE_INFO("LAYER 2D: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());
		return true;
	}

	bool Layer2D::onMouseButtonPressed(MouseButtonPressed& e)
	{
		LOG_CORE_INFO("LAYER 2D: MOUSE BUTTON PRESSED '{0}'", e.getButton());
		return true;
	}

	bool Layer2D::onMouseButtonReleased(MouseButtonReleased& e)
	{
		LOG_CORE_INFO("LAYER 2D: MOUSE BUTTON RELEASED '{0}'", e.getButton());
		return true;
	}

}