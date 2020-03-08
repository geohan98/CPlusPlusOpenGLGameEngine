#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/renderer/shader.h"
#include "../enginecode/Headers/renderer/renderAPI.h"
#include "../enginecode/Headers/OpenGL/OpenGL_shader.h"

namespace Engine
{
	namespace Renderer {
		Shader* Shader::create(const std::string& filepath)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None: return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGL_Shader(filepath);
			}
		}
	}
}