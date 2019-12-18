#include "engine_pch.h"
#include "systems/log.h"
#include "systems/renderer/uniformBuffer.h"
#include "systems/renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_uniformBuffer.h"

namespace Engine
{
	UniformBuffer* UniformBuffer::create(unsigned int size, UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_UniformBuffer(size, layout);
			break;
		default:
			LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
		}
	}

	UniformBuffer* UniformBuffer::create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return nullptr;
			break;
		default:
			LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
		}
	}
}