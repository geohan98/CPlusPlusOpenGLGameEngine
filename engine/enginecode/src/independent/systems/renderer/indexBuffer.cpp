#include "engine_pch.h"
#include "systems/renderer/indexBuffer.h"
#include "systems/renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_indexBuffer.h"

#include "systems/log.h"

namespace Engine
{
	IndexBuffer* IndexBuffer::create(unsigned int* indices, unsigned int count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_IndexBuffer(indices, count);
			break;
		default:
			LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
		}
	}
}