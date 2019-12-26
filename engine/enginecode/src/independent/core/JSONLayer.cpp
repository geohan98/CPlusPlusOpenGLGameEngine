#include "engine_pch.h"
#include "systems/log.h"
#include "core/JSONLayer.h"

#include "renderer/renderCommand.h"
#include "core/gameObject.h"
#include "components/materialComponent.h"

namespace Engine
{

	void JSONLayer::onAttach()
	{
		for (auto& renderCommand : m_initCommands) m_renderer->actionCommand(renderCommand.get());
	}

	void JSONLayer::onDetach()
	{
		for (auto& renderCommand : m_exitCommands) m_renderer->actionCommand(renderCommand.get());

		for (auto& ptr : m_data)
		{
			delete ptr;
		}
	}

	void JSONLayer::onUpdate(float timestep)
	{
		m_camera->onUpdate(timestep);
		for (auto& CGO : m_gameObjects) CGO->onUpdate(timestep);

		for (auto& renderCommand : m_predrawCommands) m_renderer->actionCommand(renderCommand.get());

		m_renderer->beginScene(m_sceneData);
		for (auto& mat : m_materials) m_renderer->submit(mat->getMaterial());

		for (auto& renderCommand : m_postdrawCommands) m_renderer->actionCommand(renderCommand.get());
	}

	void JSONLayer::onEvent(Event& e)
	{
		m_camera->onEvent(e);
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);
	}

}