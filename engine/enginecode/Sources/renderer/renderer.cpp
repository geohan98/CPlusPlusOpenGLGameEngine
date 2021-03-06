#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/renderer/renderer.h"
#include "../enginecode/Headers/renderer/renderAPI.h"
#include "../enginecode/Headers/OpenGL/OpenGL_basicRenderer.h"
#include "../enginecode/Headers/OpenGL/OpenGL_2DRenderer.h"

namespace Engine
{
	namespace Renderer {
		Renderer* Renderer::createBasic3D()
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO RENDER API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_BasicRenderer();
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO RENDER API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}

		Renderer* Renderer::createBasic2D()
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO RENDER API SELECTED");
#endif // NG_DEBUG
				break;
			case RenderAPI::API::OpenGL:
				return new OpenGL_2DRenderer();
				break;
			default:
#ifdef NG_DEBUG
				LOG_CORE_WARN("NO RENDER API SELECTED");
#endif // NG_DEBUG
				break;
			}
		}
	}
}