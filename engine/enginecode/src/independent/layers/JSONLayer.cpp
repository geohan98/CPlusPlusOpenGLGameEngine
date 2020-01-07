#include "engine_pch.h"
#include "systems/log.h"
#include "layers/JSONLayer.h"
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
	}

}