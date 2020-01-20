#include "engine_pch.h"
#include "systems/log.h"
#include "renderer/material.h"
#include "renderer/renderAPI.h"

#include "include/platform/OpenGL/OpenGL_material.h"

namespace Engine
{
	namespace Renderer {
		Material* Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None: return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGL_Material(shader, vertexArray);
			defualt: return nullptr;
			}
		}

		Material* Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexArray)
		{
			switch (RenderAPI::getAPI())
			{
			case RenderAPI::API::None: return nullptr;
			case RenderAPI::API::OpenGL: return nullptr;
			defualt: return nullptr;

			}
		}
	}
}