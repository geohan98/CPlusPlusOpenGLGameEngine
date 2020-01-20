#include "engine_pch.h"
#include "systems/log.h"
#include "renderer/renderCommand.h"
#include "renderer/renderAPI.h"

#include "include/platform/OpenGL/OpenGL_RenderCommands.h"

namespace Engine
{
	namespace Renderer {
		RenderCommand* RenderCommand::ClearDepthColourBufferCommand(bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_ClearDepthColourBufferCommand(destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}

		RenderCommand* RenderCommand::setClearColourCommand(float r, float g, float b, float a, bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setClearColourCommand(r, g, b, a, destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}

		RenderCommand* RenderCommand::setDepthTestLessCommand(bool enabled, bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setDepthTestLessCommand(enabled, destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}

		RenderCommand* RenderCommand::setBackFaceCullingCommand(bool enabled, bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setBackFaceCullingCommand(enabled, destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}
		RenderCommand* RenderCommand::setPolygonModeFill(bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setPolygonModeFill(destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}
		RenderCommand* RenderCommand::setPolygonModeLine(bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setPolygonModeLine(destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}
		RenderCommand* RenderCommand::setPolygonModePoint(bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setPolygonModePoint(destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}
		RenderCommand* RenderCommand::setBlendMode(bool enbaled, bool destroy)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_setBlendMode(enbaled, destroy);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}
	}
}