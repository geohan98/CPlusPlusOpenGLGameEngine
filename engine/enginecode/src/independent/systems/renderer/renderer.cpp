#include "engine_pch.h"
#include "systems/log.h"
#include "systems/renderer/renderer.h"
#include "systems/renderer/renderAPI.h"

#include "include/platform/OpenGL/OpenGL_basicRenderer.h"

namespace Engine
{
	Renderer* Renderer::createBasic3D()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			LOG_CORE_WARN("NO RENDER API SELECTED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGL_BasicRenderer();
			break;
		default:
			LOG_CORE_WARN("NO RENDER API SELECTED");
			break;
		}
	}
}