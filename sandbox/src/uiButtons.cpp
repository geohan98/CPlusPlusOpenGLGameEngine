#include "engine_pch.h"
#include "uiButtons.h"


namespace Engine
{


	void uiButtons::onAttach() {


		m_resourceManager = Engine::Application::getInstance().getResourceManager();
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic2D());
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.0, 0.0, 0.0, 1.0f));
		m_renderer->actionCommand(Renderer::RenderCommand::setBlendMode(true));
		m_camera = std::shared_ptr<CameraController2D>(new CameraController2D);
		m_camera->init(0.0f, 1280.0f, 720.0f, 0.0f);
	}




	void uiButtons::onDetach()
	{
	}

	void Engine::uiButtons::createButton(int anchor, std::pair<float, float> position, std::string filepath, std::pair<float, float> size) {




		std::shared_ptr<Window> m_window;


		button tempbutton = {};
		Engine::Application::getInstance().getResourceManager()->addTexture(filepath);
		Engine::Application::getInstance().getResourceManager()->getMaterial;
		tempbutton.size = size;
		tempbutton.position = position;


		if (anchor == 0) {

			tempbutton.anchorPoint = TOP_LEFT;
			tempbutton.xOffset = position.first;
			tempbutton.yOffset = position.second;


		}
		else if (anchor == 1) {

			tempbutton.anchorPoint = Engine::uiButtons::anchorPoints::TOP_RIGHT;
			tempbutton.xOffset = i_Width - position.first;
			tempbutton.yOffset = position.second;


		}

		else if (anchor == 2)
		{

			tempbutton.anchorPoint = Engine::uiButtons::anchorPoints::BOTTOM_LEFT;
			tempbutton.xOffset = position.first;
			tempbutton.yOffset = i_Height - position.second;

		}

		else if (anchor == 3)
		{

			tempbutton.anchorPoint = Engine::uiButtons::anchorPoints::BOTTOM_RIGHT;
			tempbutton.xOffset = i_Width - position.first;
			tempbutton.yOffset = i_Height - position.second;

		}

		Engine::uiButtons::m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(Engine::Application::getInstance().getResourceManager()->getMaterial("TEXT"))));
		m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(640.0f, 460.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f))));
		m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f))));
		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
		m_gameObjects.back()->addComponent(m_materials.back());
		m_gameObjects.back()->addComponent(m_positions.back());
		m_gameObjects.back()->addComponent(m_velocities.back());
		buttonstoload.push_back(tempbutton);

	};



	void uiButtons::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(false));
		m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(false));
		m_renderer->actionCommand(Renderer::RenderCommand::ClearDepthColourBufferCommand());

		std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
		ComponentMessage msg(ComponentMessageType::UniformSet, data);
		//m_materials.back()->receiveMessage(msg);


		//unsigned int texSlot = 1;
		//m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind(texSlot);
		//m_materials.back()->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
		//glm::mat4 model = glm::mat4(1.0f);
		//m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind();
		//m_resourceManager->bindFontTexture(texSlot);
		//m_renderer->submit(m_materials.back()->getMaterial());




		for (int i = 0; i < buttonstoload.size(); i++)
		{

			if (buttonstoload.at(i).anchorPoint == TOP_LEFT) //if current button anchor is top left, then do ...
			{
				buttonstoload.at(i).position.first = buttonstoload.at(i).xOffset;
				buttonstoload.at(i).position.second = buttonstoload.at(i).yOffset;
			}
			else if (buttonstoload.at(i).anchorPoint == TOP_RIGHT) //if current button anchor is top right, then do ...
			{
				buttonstoload.at(i).position.first = i_Width - buttonstoload.at(i).xOffset;
				buttonstoload.at(i).position.second = buttonstoload.at(i).yOffset;

			}
			else if (buttonstoload.at(i).anchorPoint == BOTTOM_LEFT) //if current button anchor is bottom left, then do ...
			{
				buttonstoload.at(i).position.first = buttonstoload.at(i).xOffset;
				buttonstoload.at(i).position.second = i_Height - buttonstoload.at(i).yOffset;
			}
			else if (buttonstoload.at(i).anchorPoint == BOTTOM_RIGHT) //if current button anchor is bottom right, then do ...
			{
				buttonstoload.at(i).position.first = i_Width - buttonstoload.at(i).xOffset;
				buttonstoload.at(i).position.second = i_Height - buttonstoload.at(i).yOffset;
			}

		}

	}

	void uiButtons::onEvent(Events::Event& e)
	{
		m_camera->onEvent(e);

		//Dispatch Event to Game Layer
		Events::EventDispatcher dispatcher(e);
		//Application Events
		dispatcher.dispatch<Events::WindowResize>(std::bind(&uiButtons::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowClose>(std::bind(&uiButtons::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowMoved>(std::bind(&uiButtons::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowLostFocus>(std::bind(&uiButtons::onWindowLostFocus, this, std::placeholders::_1));

	}


	bool uiButtons::onWindowResize(Events::WindowResize& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
#endif // NG_DEBUG

		return true;
	}

	bool uiButtons::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: CLOSING APPLICATION");
#endif // NG_DEBUG
		return true;
	}

	bool uiButtons::onWindowMoved(Events::WindowMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool uiButtons::onWindowLostFocus(Events::WindowLostFocus& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER 2D: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}
}