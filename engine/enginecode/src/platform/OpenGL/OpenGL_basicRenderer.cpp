#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_basicRenderer.h"
#include <glad/glad.h>

namespace Engine
{

	void OpenGL_BasicRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}

	void OpenGL_BasicRenderer::beginScene(const SceneData& sceneData)
	{
		for (auto uboPair : sceneData)
		{
			unsigned int offset = 0;
			unsigned int size;
			int i = 0;

			UniformBufferLayout layout = uboPair.first->getLayout();

			for (auto bufferElement : layout)
			{
				uboPair.first->setData(bufferElement.m_offset, bufferElement.m_size, uboPair.second[i]);
				i++;
			}
		}
	}

	void OpenGL_BasicRenderer::endScene()
	{

	}

	void OpenGL_BasicRenderer::submit(const std::shared_ptr<Material>& materials)
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

		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGL_BasicRenderer::flush()
	{

	}

}