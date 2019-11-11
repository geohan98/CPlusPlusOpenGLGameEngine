#include "engine_pch.h"
/*
#include "systems/renderer/vertexBuffer.h"
#include "systems/renderer/renderer.h"
#include "include/platform/OpenGL/OpenGL_vertexBuffer.h"

#include "systems/log.h"

namespace Engine
{
	VertexBuffer* VertexBuffer::create(float vertices, unsigned int size, BufferLayout& layout)
	{
		switch (Renderer::getAPI())
		{
		case Renderer::API::None:
			LOG_CORE_CRITICAL("NO GRAPHICS API SELECTED");
			break;
		case Renderer::API::OpenGL:
			return new OpenGL_VertexBuffer(vertices, size, layout);
			break;
		default:
			LOG_CORE_CRITICAL("UNKNOWN GRAPHICS API");
		}
	}
}*/