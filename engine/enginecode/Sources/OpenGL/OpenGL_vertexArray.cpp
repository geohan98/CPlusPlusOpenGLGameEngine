#include "engine_pch.h"
#include "../enginecode/Headers/OpenGL/OpenGL_vertexArray.h"
#include <glad/glad.h>
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/OpenGL/OpenGL_vertexBuffer.h"
#include "../enginecode/Headers/OpenGL/OpenGL_indexBuffer.h"

namespace Engine
{
	namespace Renderer {
		OpenGL_VertexArray::OpenGL_VertexArray()
		{
			glGenVertexArrays(1, &m_rendererID);
			glBindVertexArray(m_rendererID);
			LOG_CORE_INFO("[OpenGL][VERTEX ARRAY][VERTEX ARRAY CREATED WITH ID:{0}]", m_rendererID);
		}

		OpenGL_VertexArray::~OpenGL_VertexArray()
		{
			glBindVertexArray(m_rendererID);
			glDeleteVertexArrays(1, &m_rendererID);
			LOG_CORE_INFO("[OpenGL][VERTEX ARRAY][VERTEX ARRAY DESTROYED WITH ID:{0}]", m_rendererID);
		}

		void OpenGL_VertexArray::bind()
		{
			glBindVertexArray(m_rendererID);
			if (m_vertexBuffer != nullptr) m_vertexBuffer->bind();
			if (m_indexBuffer != nullptr) m_indexBuffer->bind();

		}
		void OpenGL_VertexArray::unbind()
		{
			glBindVertexArray(0);
		}
		void OpenGL_VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
		{
			glBindVertexArray(m_rendererID);
			vertexBuffer->bind();

			const auto& layout = vertexBuffer->getLayout();

			for (unsigned i = 0; i < layout.GetElements().size(); i++)
			{
				const auto& element = layout.GetElements()[i];
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, ShaderDataTypeComponentCount(element.m_dataType), ShaderDataTypeToOpenGL(element.m_dataType), element.m_normalized, layout.getStride(), (const void*)element.m_offset);
			}

			m_vertexBuffer = vertexBuffer;
		}
		void OpenGL_VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			m_indexBuffer = indexBuffer;
		}
		std::shared_ptr<VertexBuffer> OpenGL_VertexArray::getVertexBuffer() const
		{
			return m_vertexBuffer;
		}
		std::shared_ptr<IndexBuffer> OpenGL_VertexArray::getIndexBuffer() const
		{
			return m_indexBuffer;
		}
		unsigned int OpenGL_VertexArray::getDrawCount() const
		{
			if (m_indexBuffer)
			{
				return m_indexBuffer->getCount();
			}
			else if (m_vertexBuffer)
			{
				return m_vertexBuffer->getDrawCount();
			}
			return 0;
		}
	}
}