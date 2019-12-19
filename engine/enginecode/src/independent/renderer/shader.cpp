#include "engine_pch.h"
#include "systems/log.h"
#include "renderer/shader.h"
#include "renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_shader.h"

namespace Engine
{
	Shader* Shader::create(const std::string& filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGL_Shader(filepath);
		}
	}
	Shader* Shader::create(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGL_Shader(vertexFilePath, fragmentFilePath);
		}
	}
}