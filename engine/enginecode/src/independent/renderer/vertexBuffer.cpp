#include "engine_pch.h"

#include "renderer/vertexBuffer.h"
#include "renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_vertexBuffer.h"

#include "systems/log.h"

namespace Engine
{
	VertexBuffer* VertexBuffer::create(float* vertices, unsigned int count, VertexBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
#ifdef NG_DEBUG
			LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_VertexBuffer(vertices, count, layout);
			break;
		default:
#ifdef NG_DEBUG
			LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
#endif // NG_DEBUG
			break;
		}
	}
}