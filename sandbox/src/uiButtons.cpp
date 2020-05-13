#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "uiButtons.h"
#include "Headers/cameras/cameraController2D.h"
#include "Headers/fileLoaders/textLoader.h"
#include "Headers/core/application.h"
#include "Headers/systems/log.h"


namespace Engine
{


	void uiButtons::onAttach() {

		m_resourceManager = Engine::Application::getInstance().getRousrceManager();
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic2D());
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.0, 0.0, 0.0, 1.0f));
		m_renderer->actionCommand(Renderer::RenderCommand::setBlendMode(true));
		m_camera = std::shared_ptr<CameraController2D>(new CameraController2D);
		m_camera->init(0.0f, 1280.0f, 720.0f, 0.0f);

		createButton(1, { 500, 400 }, "assets/textures/buttonTest.png", { 150, 150 }, 1);
		createButton(2, { 800, 400 }, "assets/textures/buttonShiny.png", { 150, 150 }, 2);
	}




	void uiButtons::onDetach()
	{
	}

	void Engine::uiButtons::createButton(int anchor, std::pair<float, float> position, std::string filepath, std::pair<float, float> size, int texslot) {



		//unsigned int texSlot = 1;
		std::shared_ptr<Window> m_window;


		button tempbutton = {};
		Engine::Application::getInstance().getRousrceManager()->addTexture(filepath);

		tempbutton.size = size;
		tempbutton.position = position;
		tempbutton.texslot = texslot;
		tempbutton.filepath = filepath;


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


		/*float verts[4 * 5] =
		{
			-0.5f, -0.5f,0.0, 0.0f, 1.0f,
			-0.5f, 0.5f,0.0, 0.0f, 0.0f,
			0.5f, 0.5f,0.0, 1.0f, 0.0f,
			0.5f, -0.5f,0.0, 1.0f, 1.0f
		};


		unsigned int indices[4] = { 0,1,2,3 };
		*/
		/*m_resourceManager->addShader("assets/shaders/2DQuad.shader");
		m_resourceManager->addVertexArray("TEXT");
		m_resourceManager->addVertexBuffer("TEXT", verts, sizeof(verts), m_resourceManager->getShader("assets/shaders/2DQuad.shader")->getBufferLayout());
		m_resourceManager->addIndexBuffer("TEXT", indices, 4);
		m_resourceManager->getVertexArray("TEXT")->setVertexBuffer(m_resourceManager->getVertexBuffer("TEXT"));
		m_resourceManager->getVertexArray("TEXT")->setIndexBuffer(m_resourceManager->getIndexBuffer("TEXT"));
		m_resourceManager->addMaterial("TEXT", m_resourceManager->getShader("assets/shaders/2DQuad.shader"), m_resourceManager->getVertexArray("TEXT"));


		m_resourceManager->addTexture(filepath);

		Engine::uiButtons::m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(Engine::Application::getInstance().getRousrceManager()->getMaterial("TEXT"))));
		m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(tempbutton.xOffset, tempbutton.yOffset, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(tempbutton.size.first, tempbutton.size.second, 0.0f))));
		m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f))));
		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
		m_gameObjects.back()->addComponent(m_materials.back());
		m_gameObjects.back()->addComponent(m_positions.back());
		m_gameObjects.back()->addComponent(m_velocities.back());
		*/










		//m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(640.0f, 460.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 1000.0f, 100.0f))));

		/*m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f))));
		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
		m_gameObjects.back()->addComponent(m_materials.back());
		m_gameObjects.back()->addComponent(m_positions.back());
		m_gameObjects.back()->addComponent(m_velocities.back());*/



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
		//m_renderer->actionCommand(Renderer::RenderCommand::ClearDepthColourBufferCommand());

		std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
		ComponentMessage msg(ComponentMessageType::UniformSet, data);


		/*unsigned int texSlot = 1;
		m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind(texSlot);
		m_materials.back()->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
		glm::mat4 model = glm::mat4(1.0f);
		m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind();
		//m_resourceManager->bindFontTexture(texSlot);
		m_renderer->submit(m_materials.back()->getMaterial());
		*/

		//got anchors, next step linking button with anchor

		//LOG_CORE_CRITICAL(i_Width);

		for (int i = 0; i < buttonstoload.size(); i++)
		{

			/*if (buttonstoload.at(i).anchorPoint == TOP_LEFT) //if current button anchor is top left, then do ...
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
			}*/
			LOG_CORE_CRITICAL(buttonstoload.at(i).position.first);
			LOG_CORE_CRITICAL(buttonstoload.at(i).position.second);



			/*float verts[4 * 5] =
			{
				-0.5f, -0.5f,0.0, 0.0f, 1.0f,
				-0.5f, 0.5f,0.0, 0.0f, 0.0f,
				0.5f, 0.5f,0.0, 1.0f, 0.0f,
				0.5f, -0.5f,0.0, 1.0f, 1.0f
			};*/
			float verts[4 * 5] =
			{

				-0.5f, -0.5f,0.0, 0.0f, 1.0f,							//first threee position second two are UV, XYZ u v.
				-0.5f, 0.5f, 0.0, 0.0f, 0.0f,
				0.5f, 0.5f, 0.0, 1.0f, 0.0f,
				0.5f, -0.5f, 0.0, 1.0f, 1.0f
			};

			unsigned int indices[4] = { 0,1,2,3 };


			m_resourceManager->addShader("assets/shaders/Uilib/2DQuadUi.shader");
			m_resourceManager->addVertexArray("TEXT");
			m_resourceManager->addVertexBuffer("TEXT", verts, sizeof(verts), m_resourceManager->getShader("assets/shaders/Uilib/2DQuadUi.shader")->getBufferLayout());
			m_resourceManager->addIndexBuffer("TEXT", indices, 4);
			m_resourceManager->getVertexArray("TEXT")->setVertexBuffer(m_resourceManager->getVertexBuffer("TEXT"));
			m_resourceManager->getVertexArray("TEXT")->setIndexBuffer(m_resourceManager->getIndexBuffer("TEXT"));
			m_resourceManager->addMaterial("TEXT", m_resourceManager->getShader("assets/shaders/Uilib/2DQuadUi.shader"), m_resourceManager->getVertexArray("TEXT"));


			m_resourceManager->addTexture(buttonstoload.at(i).filepath);

			Engine::uiButtons::m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(Engine::Application::getInstance().getRousrceManager()->getMaterial("TEXT"))));
			m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(buttonstoload.at(i).position.first, buttonstoload.at(i).position.second, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(buttonstoload.at(i).size.first, buttonstoload.at(i).size.second, 0.0f))));
			m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f))));
			m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
			m_gameObjects.back()->addComponent(m_materials.back());
			m_gameObjects.back()->addComponent(m_positions.back());
			m_gameObjects.back()->addComponent(m_velocities.back());
			m_materials.back()->receiveMessage(msg);
			unsigned int texSlot = buttonstoload.at(i).texslot;
			//unsigned int texSlot = 1;
			m_resourceManager->getTexture(buttonstoload.at(i).filepath)->bind(texSlot);
			m_materials.back()->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
			glm::mat4 model = glm::mat4(1.0f);
			m_resourceManager->getTexture(buttonstoload.at(i).filepath)->bind();
			//m_resourceManager->bindFontTexture(texSlot);
			m_renderer->submit(m_materials.back()->getMaterial());



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
		LOG_CORE_INFO("Ui Buttons: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
#endif // NG_DEBUG

		i_Width = e.getWidth();
		i_Height = e.getHeight();



		return true;
	}

	bool uiButtons::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("Ui Buttons: CLOSING APPLICATION");
#endif // NG_DEBUG
		return true;
	}

	bool uiButtons::onWindowMoved(Events::WindowMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("Ui Buttons: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool uiButtons::onWindowLostFocus(Events::WindowLostFocus& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("Ui Buttons:: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}


}