#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/OpenGL/OpenGL_basicRenderer.h"
#include <glad/glad.h>

namespace Engine
{
	namespace Renderer {
		void OpenGL_BasicRenderer::actionCommand(RenderCommand* command)
		{
			command->action();
			if (command->destroyOnAction)
			{
				delete command;
			}
		}

		void OpenGL_BasicRenderer::beginScene(const SceneData& sceneData)
		{
			for (auto uboPair : sceneData)
			{
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
			if (materials->getGeometry().index() == 0)
			{
				//LOG_CORE_INFO("OpenGL: VARIANT WAS VERTEX ARRAY");
				auto geometry = std::get<std::shared_ptr<VertexArray>>(materials->getGeometry());
				geometry->bind();

				auto perDrawData = materials->getData();
				for (auto dataPair : perDrawData)
				{
					shader->uploadData(dataPair.first, dataPair.second);
				}

				glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				//LOG_CORE_INFO("OpenGL: VARIANT WAS VERTEX BUFFER");
				auto geometry = std::get<std::shared_ptr<VertexBuffer>>(materials->getGeometry());
				geometry->bind();

				auto perDrawData = materials->getData();
				for (auto dataPair : perDrawData)
				{
					shader->uploadData(dataPair.first, dataPair.second);
				}

				auto VAO = std::shared_ptr<VertexArray>(VertexArray::create());

				VAO->setVertexBuffer(geometry);
				VAO->bind();

				glDrawArrays(GL_POINTS, 0, geometry->getDrawCount());
			}
		}

		void OpenGL_BasicRenderer::flush()
		{

		}

	}
}
