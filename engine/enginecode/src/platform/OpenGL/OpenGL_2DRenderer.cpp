#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_2DRenderer.h"
#include <glad/glad.h>

namespace Engine
{

	void OpenGL_2DRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}

	void OpenGL_2DRenderer::submit(const std::shared_ptr<Material>& materials)
	{
		auto shader = materials->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(materials->getGeometry());
		geometry->bind();

		auto perDrawData = materials->getData();
		for (auto dataPair : perDrawData)
		{
			shader->uploadData(dataPair.first, dataPair.second);
		}

		glDrawElements(GL_QUADS, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

}