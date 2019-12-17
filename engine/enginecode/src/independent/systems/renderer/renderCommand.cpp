#include "engine_pch.h"
#include "systems/log.h"
#include "systems/renderer/renderCommand.h"
#include "systems/renderer/renderAPI.h"

#include "include/platform/OpenGL/OpenGL_RenderCommands.h"

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
			return new OpenGL_ClearDepthColourBufferCommand();
			break;
		default:
			break;
		}
	}

	Engine::RenderCommand* RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_WARN("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_setClearColourCommand(r, g, b, a);
			break;
		default:
			break;
		}
	}

	Engine::RenderCommand* RenderCommand::setDepthTestLessCommand(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_WARN("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_setDepthTestLessCommand(enabled);
			break;
		default:
			break;
		}
	}

	Engine::RenderCommand* RenderCommand::setBackFaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_WARN("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_setBackFaceCullingCommand(enabled);
			break;
		default:
			break;
		}
	}
}