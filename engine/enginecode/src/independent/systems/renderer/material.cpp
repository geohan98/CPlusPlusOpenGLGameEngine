#include "engine_pch.h"
#include "systems/log.h"
#include "systems/renderer/material.h"
#include "systems/renderer/renderAPI.h"

namespace Engine
{
	Material* Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		return nullptr;
	}

	Material* Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexArray)
	{
		return nullptr;
	}
}