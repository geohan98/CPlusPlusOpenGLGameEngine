#include "engine_pch.h"

#include "systems/renderer/vertexArray.h"
#include "systems/renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_vertexArray.h"

#include "systems/log.h"

namespace Engine
{
	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_VertexArray();
			break;
		default:
			LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
		}
	}
}