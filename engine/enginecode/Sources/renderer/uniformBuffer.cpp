#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/renderer/uniformBuffer.h"
#include "../enginecode/Headers/renderer/renderAPI.h"
#include "../enginecode/Headers/OpenGL/OpenGL_uniformBuffer.h"

namespace Engine
{
	namespace Renderer {
		UniformBuffer* UniformBuffer::create(unsigned int size, UniformBufferLayout& layout)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_UniformBuffer(size, layout);
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
#endif // NG_DEBUG
				break;
			}
		}

		UniformBuffer* UniformBuffer::create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return nullptr;
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