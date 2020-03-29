#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "Headers/OpenGL/OpenGL_basicRenderer.h"
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

		void OpenGL_BasicRenderer::submit(const std::shared_ptr<Material>& materials, RendererDrawType _drawType)
		{
			std::shared_ptr<Shader> shader = materials->getShader();
			shader->bind();
			std::shared_ptr<VertexArray> vertexArray = std::get<std::shared_ptr<VertexArray>>(materials->getGeometry());
			vertexArray->bind();

			auto perDrawData = materials->getData();
			for (auto dataPair : perDrawData)
			{
				shader->uploadData(dataPair.first, dataPair.second);
			}

			switch (_drawType)
			{
			case Engine::Renderer::Triangle:
				glDrawElements(GL_TRIANGLES, vertexArray->getDrawCount(), GL_UNSIGNED_INT, 0);
				//glDrawArrays(GL_TRIANGLES, 0, vertexArray->getDrawCount());
				break;
			case Engine::Renderer::Lines:
				glDrawArrays(GL_LINES, 0, vertexArray->getDrawCount());
				break;
			case Engine::Renderer::Point:
				//glDrawElements(GL_POINTS, vertexArray->getDrawCount(), GL_UNSIGNED_INT, 0);
				glDrawArrays(GL_POINTS, 0, vertexArray->getDrawCount());
				break;
			default:
				LOG_CORE_ERROR("[RENDERER][OPENGL][NO DRAW TYPE SPECIFIED]");
				break;
			}
		}

		void OpenGL_BasicRenderer::flush()
		{

		}

	}
}
