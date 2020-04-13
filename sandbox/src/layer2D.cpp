#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "layer2D.h"
#include "Headers/cameras/cameraController2D.h"
#include "Headers/fileLoaders/textLoader.h"


namespace Engine
{

	void Layer2D::onAttach()
	{
		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic2D());
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
		m_renderer->actionCommand(Renderer::RenderCommand::setBlendMode(true));
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
		m_resourceManager->addMaterial("TEXT", m_resourceManager->getShader("assets/shaders/2DQuad.shader"), m_resourceManager->getVertexArray("TEXT"));

		m_resourceManager->addTexture("assets/textures/buttonTest.png");
		m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(m_resourceManager->getMaterial("TEXT"))));
		m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(400.0f, 75.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 1.0f, 1.0f))));
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

		m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(false));
		m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(false));

		std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
		ComponentMessage msg(ComponentMessageType::UniformSet, data);
		m_materials.back()->receiveMessage(msg);

		unsigned int texSlot = 1;
		m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind(texSlot);
		m_materials.back()->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
		glm::mat4 model = glm::mat4(1.0f);
		m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind();

		m_renderer->submit(m_materials.back()->getMaterial());
	}

	struct Button {
		std::pair<float, float> size;
		std::pair<float, float> position;
	};



	void Layer2D::onEvent(Events::Event& e)
	{
		m_camera->onEvent(e);

		//Dispatch Event to Game Layer
		Events::EventDispatcher dispatcher(e);
		//Application Events
		dispatcher.dispatch<Events::WindowResize>(std::bind(&Layer2D::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowClose>(std::bind(&Layer2D::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowMoved>(std::bind(&Layer2D::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowLostFocus>(std::bind(&Layer2D::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispatcher.dispatch<Events::KeyPressed>(std::bind(&Layer2D::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyReleased>(std::bind(&Layer2D::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyTyped>(std::bind(&Layer2D::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispatcher.dispatch<Events::MouseMoved>(std::bind(&Layer2D::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseScrolled>(std::bind(&Layer2D::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseButtonPressed>(std::bind(&Layer2D::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseButtonReleased>(std::bind(&Layer2D::onMouseButtonReleased, this, std::placeholders::_1));
	}

	bool Layer2D::onWindowResize(Events::WindowResize& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: CLOSING APPLICATION");
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onWindowMoved(Events::WindowMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onWindowLostFocus(Events::WindowLostFocus& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onKeyPressed(Events::KeyPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: KEY PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onKeyReleased(Events::KeyReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: KEY RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onKeyTyped(Events::KeyTyped& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: KEY TYPED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onMouseMove(Events::MouseMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onMouseScrolled(Events::MouseScrolled& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onMouseButtonPressed(Events::MouseButtonPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: MOUSE BUTTON PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool Layer2D::onMouseButtonReleased(Events::MouseButtonReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: MOUSE BUTTON RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

}