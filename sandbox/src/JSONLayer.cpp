#include "engine_pch.h"
#include "systems/log.h"
#include "JSONLayer.h"
#include "fileLoaders/JSONLoader.h"

namespace Engine
{

	void JSONLayer::onAttach()
	{
		JSONLoader::load(m_filepath, *this);
		//Init Render Commands
		for (auto& renderCommand : m_initCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
	}

	void JSONLayer::onDetach()
	{
		//Exit Render Commands
		for (auto& renderCommand : m_exitCommands) m_renderer->actionCommand(renderCommand.get());

		for (auto& ptr : m_data)
		{
			delete ptr;
		}
	}

	void JSONLayer::onUpdate(float deltaTime)
	{

		m_camera->onUpdate(deltaTime);

		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		for (auto& mat : m_materials)
		{
			std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			mat->receiveMessage(msg);
			m_renderer->submit(mat->getMaterial());
		}

		//Pre Draw Render Commands
		for (auto& renderCommand : m_predrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}

		m_renderer->beginScene(m_sceneData);



		for (auto& mat : m_materials)
		{
			m_renderer->submit(mat->getMaterial());
		}
		//Post Draw Render Commands
		for (auto& renderCommand : m_postdrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
	}

	void JSONLayer::onEvent(Event& e)
	{
		m_camera->onEvent(e);
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);

		//Dispatch Event to JSONLayer
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyReleased>(std::bind(&JSONLayer::onKeyReleased, this, std::placeholders::_1));
	}

	bool JSONLayer::onWindowResize(WindowResize& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onWindowClose(WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: CLOSING APPLICATION");
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onWindowMoved(WindowMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onWindowLostFocus(WindowLostFocus& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onKeyPressed(KeyPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: KEY PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onKeyReleased(KeyReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: KEY RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG
		if (e.getButton() == KEY_R)
		{
#ifdef NG_DEBUG
			LOG_CORE_INFO("JSONLayer: RESET CAMERA");
#endif // NG_DEBUG
			m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);
		}
		if (e.getButton() == KEY_1)
		{
#ifdef NG_DEBUG
			LOG_CORE_INFO("JSONLayer: Fill Render Mode");
#endif // NG_DEBUG
			m_renderer->actionCommand(RenderCommand::setPolygonModeFill());
		}
		if (e.getButton() == KEY_2)
		{
#ifdef NG_DEBUG
			LOG_CORE_INFO("JSONLayer: Line Render ModeA");
#endif // NG_DEBUG
			m_renderer->actionCommand(RenderCommand::setPolygonModeLine());
		}
		if (e.getButton() == KEY_3)
		{
#ifdef NG_DEBUG
			LOG_CORE_INFO("JSONLayer: Point Render Mode");
#endif // NG_DEBUG
			m_renderer->actionCommand(RenderCommand::setPolygonModePoint());
		}
		return true;
	}

	bool JSONLayer::onKeyTyped(KeyTyped& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: KEY TYPED '{0}'", e.getButton());
#endif // NG_DEBUG

		return true;
	}

	bool JSONLayer::onMouseMove(MouseMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onMouseScrolled(MouseScrolled& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onMouseButtonPressed(MouseButtonPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: MOUSE BUTTON PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

	bool JSONLayer::onMouseButtonReleased(MouseButtonReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("JSONLayer: MOUSE BUTTON RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG
		return true;
	}

}