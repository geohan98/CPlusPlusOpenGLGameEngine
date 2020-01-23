#include "engine_pch.h"
#include "../enginecode/Headers/renderer/vertexBuffer.h"
#include "../enginecode/Headers/renderer/renderAPI.h"
#include "../enginecode/Headers/OpenGL/OpenGL_vertexBuffer.h"
#include "../enginecode/Headers/systems/log.h"

namespace Engine
{
	namespace Renderer {
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
}