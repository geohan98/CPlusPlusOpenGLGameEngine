#include "engine_pch.h"

#include "renderer/vertexArray.h"
#include "renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_vertexArray.h"

#include "systems/log.h"

namespace Engine
{
	namespace Renderer {
		VertexArray* VertexArray::create()
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_VertexArray();
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
#endif // NG_DEBUG
				break;
			}
		}
	}
}