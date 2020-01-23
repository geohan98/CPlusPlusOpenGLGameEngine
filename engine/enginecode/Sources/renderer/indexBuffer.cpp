#include "engine_pch.h"
#include "../enginecode/Headers/renderer/indexBuffer.h"
#include "../enginecode/Headers/renderer/renderAPI.h"
#include "../enginecode/Headers/OpenGL/OpenGL_indexBuffer.h"

#include "../enginecode/Headers/systems/log.h"

namespace Engine
{
	namespace Renderer {
		IndexBuffer* IndexBuffer::create(unsigned int* indices, unsigned int count)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_IndexBuffer(indices, count);
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