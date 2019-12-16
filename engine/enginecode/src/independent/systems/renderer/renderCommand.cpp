#include "engine_pch.h"
#include "systems/log.h"
#include "systems/renderer/renderCommand.h"
#include "systems/renderer/renderAPI.h"

namespace Engine
{
	Engine::RenderCommand* RenderCommand::ClearDepthColourBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_WARN("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			break;
		default:
			break;
		}
	}

	Engine::RenderCommand* RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{

	}

	Engine::RenderCommand* RenderCommand::setDepthTestLessCommand(bool enabled)
	{

	}

	Engine::RenderCommand* RenderCommand::setBackFaceCullingCommand(bool enabled)
	{

	}
}